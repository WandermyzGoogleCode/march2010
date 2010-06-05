using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.IO;
using System.Web;

namespace RemoteService
{
    public class ServerCaller
    {
        private const string SERVER_URL = "http://server.lives3.net/";
        private const int MAX_UPDATE_REQUEST_NUMBER = 16;
        private const int SIZE_UPDATE_ENTRY = 1328;

        private enum ServerOperation
        {
            Register = 11,
            Update = 12,
            GetUpdatePackage = 13,
            Test = 19
        }

        private ServerCallerErrorCallback errorCallback;

        public ServerCaller(ServerCallerErrorCallback errorCallback)
        {
            this.errorCallback = errorCallback;
        }

        /// <summary>
        /// 用户注册
        /// </summary>
        /// <param name="encryptedPhoneNumber">加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber</param>
        /// <param name="userEntry">用服务器公钥做加密后得到的UserEntry</param>
        /// <returns>一个bool表示成功或者失败</returns>
        public bool EncryptedRegister(byte[] encryptedPhoneNumber, byte[] userEntry)
        {
            Dictionary<string, string> postData = new Dictionary<string, string>();
            postData.Add("encryptedPhoneNumber", Convert.ToBase64String(encryptedPhoneNumber));
            postData.Add("userEntry", Convert.ToBase64String(userEntry));

            WebRequest request = sendWebRequest(ServerOperation.Register, postData);
            if (request == null)
                return false;

            string response = getResponse(request);
            if (response != "1")
            {
                errorCallback("服务器返回错误信息：\n" + response, new Exception());
                return false;
            }

            return true;
        }

        /// <summary>
        /// 用户更新自己的信息
        /// </summary>
        /// <param name="encryptedPhoneNumber">加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber</param>
        /// <param name="userEntry">先用服务器公钥做加密，再用用户自己的私钥加密后得到的UserEntry</param>
        /// <returns>一个bool表示成功或者失败</returns>
        public bool EncryptedUpdate(byte[] encryptedPhoneNumber, byte[] userEntry)
        {
            Dictionary<string, string> postData = new Dictionary<string, string>();
            postData.Add("encryptedPhoneNumber", Convert.ToBase64String(encryptedPhoneNumber));
            postData.Add("userEntry", Convert.ToBase64String(userEntry));

            WebRequest request = sendWebRequest(ServerOperation.Update, postData);
            if (request == null)
                return false;

            string response = getResponse(request);
            if (response != "1")
            {
                errorCallback("服务器返回错误信息：\n" + response, new Exception());
                return false;
            }

            return true;
        }

        /// <summary>
        /// 用户获取自己联系人的最新信息
        /// </summary>
        /// <param name="encryptedPhoneNumber">加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber</param>
        /// <param name="updateRequest">普通的UpdateRequest，其中包含了需要获得哪些联系人的最新信息（加密过的）</param>
        /// <param name="threshold">用户最后更新的时间，用于做增量更新。格式为Unix时间戳格式</param>
        /// <example>
        /// DateTime dt = DateTime.Now;
        /// int unixtime = (dt - new DateTime(1970, 1, 1)).TotalSeconds;
        /// </example>
        /// <returns>获得的UpdatePackage列表，包含了更新过的联系人信息（已经做了时间增量处理）。若失败则返回null</returns>
        public List<byte[]> GetEncryptedUpdatePackage(byte[] encryptedPhoneNumber, List<byte[]> updateRequest, Int64 threshold)
        {
            if (updateRequest.Count > MAX_UPDATE_REQUEST_NUMBER)
            {
                throw new ArgumentException("updateRequest条目的最大数量为" + MAX_UPDATE_REQUEST_NUMBER.ToString());
            }
            
            Dictionary<string, string> postData = new Dictionary<string, string>();
            postData.Add("encryptedPhoneNumber", Convert.ToBase64String(encryptedPhoneNumber));
            postData.Add("threshold", Convert.ToBase64String(BitConverter.GetBytes(threshold)));

            int counter = 0;
            foreach (byte[] data in updateRequest)
            {
                postData.Add(string.Format("updateEntry[{0}]", counter), Convert.ToBase64String(data));
                counter++;
            }

            WebRequest request = sendWebRequest(ServerOperation.GetUpdatePackage, postData);

            List<byte[]> result = new List<byte[]>();
            BinaryReader br = null;
            try
            {
                WebResponse response = request.GetResponse();
                if (response.ContentType != "application/octet-stream")
                {
                    errorCallback("服务器没有返回二进制数据，返回的数据为：\n" 
                        + new StreamReader(response.GetResponseStream()).ReadToEnd(), new Exception());
                }

                br = new BinaryReader(response.GetResponseStream());

                int nOfEntry = br.ReadInt32();
                for (int i = 0; i < nOfEntry; i++)
                {
                    byte[] data = br.ReadBytes(SIZE_UPDATE_ENTRY);
                    result.Add(data);
                }
            }
            catch (Exception e)
            {
                errorCallback(e.Message, e);
                result = null;
            }
            finally
            {
                if (br != null)
                    br.Close();
            }

            return result;
        }

        /// <summary>
        /// 新建一个Web Request并发送请求，返回该Web Request。将通过ServerCallerErrorCallback返回错误信息
        /// </summary>
        /// <param name="op">服务器端操作码</param>
        /// <param name="postData">POST数据，key为变量名，value为值（将做URL Encode）</param>
        private WebRequest sendWebRequest(ServerOperation op, Dictionary<string, string> postData)
        {
            WebRequest webRequest = WebRequest.Create(string.Format("{0}?op={1}", SERVER_URL, (int)op));
            webRequest.ContentType = "application/x-www-form-urlencoded";
            webRequest.Method = "POST";

            string postStr = "";
            foreach (KeyValuePair<string, string> entry in postData)
            {
                postStr += entry.Key + "=" + HttpUtility.UrlEncode(entry.Value) + "&";
            }

            byte[] bytes = Encoding.ASCII.GetBytes(postStr);
            Stream os = null;
            try
            {
                webRequest.ContentLength = bytes.Length;
                os = webRequest.GetRequestStream();
                os.Write(bytes, 0, bytes.Length);
            }
            catch (Exception e)
            {
                errorCallback(e.Message, e);
                webRequest = null;
            }
            finally
            {
                if (os != null)
                {
                    os.Close();
                }
            }

            return webRequest;
        }

        /// <summary>
        /// 取得Web Request的Response。将通过ServerCallerErrorCallback返回错误信息
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private string getResponse(WebRequest request)
        {
            string result = null;
            StreamReader sr = null;
            try
            {
                WebResponse response = request.GetResponse();
                sr = new StreamReader(response.GetResponseStream());
                result = sr.ReadToEnd();
            }
            catch (Exception e)
            {
                errorCallback(e.Message, e);
            }
            finally
            {
                if (sr != null)
                    sr.Close();
            }

            return result;
        }
    }

    /// <summary>
    /// 当网络传输发生错误时的回调函数定义
    /// </summary>
    /// <param name="errorMsg">错误消息</param>
    /// <param name="e">相关的Exception</param>
    public delegate void ServerCallerErrorCallback(string errorMsg, Exception e);
}
