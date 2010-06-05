using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace VirtualMobile
{
    [Serializable]
    public class User
    {
        private string phoneNum;
        private string name;
        private string status;
        private string codeword;
        private List<Contact> connections = new List<Contact>();
        private byte[] userPrivateKeyMem;

        public string PhoneNum 
        { 
            get
            {
                return phoneNum;
            }
            set
            {
                phoneNum = value;
            }
        }

        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }

        public string Status
        {
            get
            {
                return status;
            }
            set
            {
                status = value;
            }
        }

        public string Codeword
        {
            get
            {
                return codeword;
            }
            set
            {
                codeword = value;
            }
        }

        public List<Contact> Connections 
        {
            get
            {
                return connections;
            }
            set
            {
                connections = value;
            }
        }

        public byte[] UserPrivateKeyMem
        {
            get
            {
                return userPrivateKeyMem;
            }
            set
            {
                userPrivateKeyMem = value;
            }
        }
    }

    [Serializable]
    public class Contact
    {
        private string phoneNum;
        private string name;
        private string status;
        int lastUpdateTime;

        public Contact(string pn, string name, string status)
        {
            phoneNum = pn;
            this.name = name;
            this.status = status;
            lastUpdateTime = 0;
        }

        public Contact(string pn, string name, string status, int t)
        {
            phoneNum = pn;
            this.name = name;
            this.status = status;
            lastUpdateTime = t;
        }

        public string PhoneNum
        {
            get
            {
                return phoneNum;
            }
            set
            {
                phoneNum = value;
            }
        }

        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }

        public string Status
        {
            get
            {
                return status;
            }
            set
            {
                status = value;
            }
        }

        public int LastUpdateTime
        {
            get
            {
                return lastUpdateTime;
            }
            set
            {
                lastUpdateTime = value;
            }
        }
    }
}
