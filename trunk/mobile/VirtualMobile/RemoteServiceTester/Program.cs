using System;
using System.Collections.Generic;
using System.Text;
using RemoteService;

namespace RemoteServiceTester
{
    class Program
    {
        static void Main(string[] args)
        {
            ServerCaller caller = new ServerCaller(errorCallback);
            bool result = caller.EncryptedRegister(Encoding.UTF8.GetBytes("今天心情"), Encoding.UTF8.GetBytes("很好!"));
            Console.WriteLine(result);
        }

        static void errorCallback(string errMsg, Exception e)
        {
            Console.WriteLine(errMsg);
        }
    }
}
