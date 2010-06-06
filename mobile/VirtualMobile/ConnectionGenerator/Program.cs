using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using VirtualMobile;

namespace ConnectionGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            if(args.Length != 3)
            {
                Console.WriteLine("filepath phoneNumber_first num");
            }
            string filepath = args[0];
            Int64 phoneNumber = Int64.Parse(args[1]);
            Int64 num = Int64.Parse(args[2]);
            
            FileStream fs;
            try
            {
                fs = new FileStream(filepath, FileMode.Open);
            }
            catch (Exception e)
            {
                Console.WriteLine("无法打开文件（{0}）", e.Message);
                return;
            }

            BinaryFormatter bf = new BinaryFormatter();

            User user;
            try
            {
                user = bf.Deserialize(fs) as User;
            }
            catch (Exception e)
            {
                Console.WriteLine("反序列化失败（{0}）", e.Message);
                return;
            }
            fs.Close();

            for (Int64 pn = phoneNumber; pn < phoneNumber + num; pn++)
            {
                Contact c = new Contact(pn.ToString(), "", "");
                user.Connections.Add(c);
            }

            try
            {
                fs = new FileStream(filepath, FileMode.Create);
            }
            catch (Exception e)
            {
                Console.WriteLine("文件无法写入（{0}）", e.Message);
                return;
            }

            try
            {
                bf.Serialize(fs, user);
            }
            catch (Exception e)
            {
                Console.WriteLine("序列化失败（{0}）", e.Message);
                return;
            }

            Console.WriteLine("{0}个联系人搞定！", num);
        }
    }
}
