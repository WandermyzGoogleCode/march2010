using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.IO;
using RemoteService;
using System.Windows.Forms;

namespace VirtualMobile
{
    class DataOperation
    {
        private DataTable dt;
        private ServerCaller caller;

        public DataOperation(DataTable dt)
        {
            this.dt = dt;
            caller = new ServerCaller(errorCallback);
        }

        public bool Register(User u)
        {
            BinaryWriter writer = new BinaryWriter(new FileStream(Constants.TMP_DIR + "to_c.tmp", FileMode.OpenOrCreate, FileAccess.Write));
            writeStringToFile(writer, u.PhoneNum, Constants.NUMBER_STR_LEN);
            writeStringToFile(writer, u.Name, Constants.MAX_NAME_LENGTH);
            writeStringToFile(writer, u.Status, Constants.MAX_STATUS_LENGTH);
            writer.Write((int)Encoding.UTF8.GetBytes(u.Codeword).Length);
            writeStringToFile(writer, u.Codeword, -1);
            writer.Close();
         
            System.Diagnostics.Process p = new System.Diagnostics.Process();
#if DEBUG
            try
            {
                p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/register_converter.exe";
                p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
            }
            catch (Exception)
            { }
#else
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/register_converter.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#endif
            p.StartInfo.CreateNoWindow = true;
            p.Start();
            p.WaitForExit();
            p.Close();

            BinaryReader reader = new BinaryReader(new FileStream(Constants.TMP_DIR + "from_c.tmp", FileMode.Open, FileAccess.Read));
            byte[] encryptedPhoneNum = new byte[Constants.ENCRYPTED_PHONENUM_LENGTH];
            byte[] userEntry = new byte[Constants.SIZE_USERENTRY];
            byte[] privateKeyMem = new byte[Constants.SIZE_PRIVATEKEY_MEM];
            reader.Read(encryptedPhoneNum, 0, Constants.ENCRYPTED_PHONENUM_LENGTH);
            reader.Read(userEntry, 0, Constants.SIZE_USERENTRY);
            reader.Read(privateKeyMem, 0, Constants.SIZE_PRIVATEKEY_MEM);
            reader.Close();

            System.IO.File.Delete(Constants.TMP_DIR + "to_c.tmp");
            System.IO.File.Delete(Constants.TMP_DIR + "from_c.tmp");

            if (!caller.EncryptedRegister(encryptedPhoneNum, userEntry))
            {
                MessageBox.Show("ServerCaller failed!");
                return false;
            }
            u.UserPrivateKeyMem = privateKeyMem;
            return true;
        }

        public void Update(User u, bool codewordChanged)
        {
            BinaryWriter writer = new BinaryWriter(new FileStream(Constants.TMP_DIR + "to_c.tmp", FileMode.OpenOrCreate, FileAccess.Write));
            writeStringToFile(writer, u.PhoneNum, Constants.NUMBER_STR_LEN);
            writeStringToFile(writer, u.Name, Constants.MAX_NAME_LENGTH);
            writeStringToFile(writer, u.Status, Constants.MAX_STATUS_LENGTH);
            if (codewordChanged)
            {
                writer.Write((int)Encoding.UTF8.GetBytes(u.Codeword).Length);
                writeStringToFile(writer, u.Codeword, -1);
            }
            else
                writer.Write((int)0);
            writer.Write(u.UserPrivateKeyMem, 0, Constants.SIZE_PRIVATEKEY_MEM);            writer.Write((int)u.Connections.Count);
            foreach (Contact c in u.Connections)
                writeStringToFile(writer, c.PhoneNum, Constants.NUMBER_STR_LEN);
            writer.Close();

            System.Diagnostics.Process p = new System.Diagnostics.Process();
#if DEBUG
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/update_converter.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#else
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/update_converter.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#endif
            p.Start();
            p.WaitForExit();
            p.Close();

            BinaryReader reader = new BinaryReader(new FileStream(Constants.TMP_DIR + "from_c.tmp", FileMode.Open, FileAccess.Read));
            byte[] encryptedPhoneNum = new byte[Constants.ENCRYPTED_PHONENUM_LENGTH];
            byte[] userEntry = new byte[Constants.SIZE_USERENTRY];
            byte[] privateKeyMem = new byte[Constants.SIZE_PRIVATEKEY_MEM];
            reader.Read(encryptedPhoneNum, 0, Constants.ENCRYPTED_PHONENUM_LENGTH);
            reader.Read(userEntry, 0, Constants.SIZE_USERENTRY);
            reader.Read(privateKeyMem, 0, Constants.SIZE_PRIVATEKEY_MEM);
            reader.Close();

            System.IO.File.Delete(Constants.TMP_DIR + "to_c.tmp");
            System.IO.File.Delete(Constants.TMP_DIR + "from_c.tmp");

            if (!caller.EncryptedUpdate(encryptedPhoneNum, userEntry))
                MessageBox.Show("ServerCaller failed!");
            u.UserPrivateKeyMem = privateKeyMem;
        }

        public void Getinfo(User u, List<Contact> requests, Int64 threshold)
        {
            BinaryWriter writer = new BinaryWriter(new FileStream(Constants.TMP_DIR + "to_c.tmp", FileMode.OpenOrCreate, FileAccess.Write));
            writeStringToFile(writer, u.PhoneNum, Constants.NUMBER_STR_LEN);
            writer.Write((int)requests.Count);
            for (int i = 0; i < requests.Count; i++)
            {
                writeStringToFile(writer, requests[i].PhoneNum, Constants.NUMBER_STR_LEN);
            }            
            writer.Close();

            System.Diagnostics.Process p = new System.Diagnostics.Process();
#if DEBUG
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/getinfo_converter_1.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#else
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/getinfo_converter_1.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#endif
            p.Start();
            p.WaitForExit();
            p.Close();

            BinaryReader reader = new BinaryReader(new FileStream(Constants.TMP_DIR + "from_c.tmp", FileMode.Open, FileAccess.Read));
            byte[] encryptedPhoneNum = new byte[Constants.ENCRYPTED_PHONENUM_LENGTH];
            reader.Read(encryptedPhoneNum, 0, Constants.ENCRYPTED_PHONENUM_LENGTH);

            int num = reader.ReadInt32();
            List<byte[]> updateRequest = new List<byte[]>();
            for (int i = 0; i < num; i++)
            {
                byte[] epn = new byte[Constants.ENCRYPTED_PHONENUM_LENGTH];
                reader.Read(epn, 0, Constants.ENCRYPTED_PHONENUM_LENGTH);
                updateRequest.Add(epn);
            }
            reader.Close();

            System.IO.File.Delete(Constants.TMP_DIR + "to_c.tmp");
            System.IO.File.Delete(Constants.TMP_DIR + "from_c.tmp");

            List<byte[]> updatePackage = caller.GetEncryptedUpdatePackage(encryptedPhoneNum, updateRequest, threshold);
            if (updateRequest == null || updateRequest.Count == 0)
            {
                MessageBox.Show("Server caller failed!");
                return;
            }

            if (updateRequest.Count == 0)
            {
                return; 
            }

            int numOfUpdateEntry = updatePackage.Count;
            writer = new BinaryWriter(new FileStream(Constants.TMP_DIR + "to_c.tmp", FileMode.OpenOrCreate, FileAccess.Write));
            writer.Write((int)numOfUpdateEntry);
            for (int i = 0; i < numOfUpdateEntry; i++)
            {
                byte[] entry = updatePackage[i];
                writer.Write(entry, 0, Constants.SIZE_UPDATE_ENTRY);
            }
            writer.Write(u.UserPrivateKeyMem, 0, Constants.SIZE_PRIVATEKEY_MEM);
            writer.Close();

            p = new System.Diagnostics.Process();
#if DEBUG
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/getinfo_converter_2.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#else
            p.StartInfo.FileName = Directory.GetCurrentDirectory() + "/cbin/getinfo_converter_2.exe";
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory() + "/cbin";
#endif
            p.Start();
            p.WaitForExit();
            p.Close();

            reader = new BinaryReader(new FileStream(Constants.TMP_DIR + "from_c.tmp", FileMode.Open, FileAccess.Read));
            numOfUpdateEntry = reader.ReadInt32();
            for (int i = 0; i < numOfUpdateEntry; i++)
            {
                long phone = reader.ReadInt64();
                byte[] bName = reader.ReadBytes(Constants.MAX_NAME_LENGTH);
                byte[] bStatus = reader.ReadBytes(Constants.MAX_STATUS_LENGTH);
                string name = Encoding.UTF8.GetString(bName);
                string status = Encoding.UTF8.GetString(bStatus);
                int pos1 = name.IndexOf('\0');
                int pos2 = status.IndexOf('\0');
                name = name.Substring(0, pos1);
                status = status.Substring(0, pos2);
                for (int j = 0; j < dt.Rows.Count; j++)
                {
                    if (long.Parse((string)dt.Rows[j][0]) == phone)
                    {
                        dt.Rows[j][1] = name;
                        dt.Rows[j][2] = status;
                        dt.Rows[j].AcceptChanges();
                    }
                }
            }
            reader.Close();
        }

        static void errorCallback(string errMsg, Exception e)
        {
            MessageBox.Show(errMsg);
        }

        private void writeStringToFile(BinaryWriter writer, string s, int totalLen)
        {
            byte[] data = Encoding.UTF8.GetBytes(s);
            int len = data.Length;            
            try
            {
                writer.Write(data);
                if (totalLen != -1)
                {
                    for (int i = 0; i < totalLen - len; i++)
                        writer.Write('\0');
                }
            }
            catch (Exception) {
                return;
            }
        }
    }
}
