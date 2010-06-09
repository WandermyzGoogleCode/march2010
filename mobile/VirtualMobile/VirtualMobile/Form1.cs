using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace VirtualMobile
{
    public partial class mainForm : Form
    {
        private DataTable dt;
        private DataOperation oper;
        private User currentUser;

        public mainForm()
        {
            InitializeComponent();
            
            dt = new DataTable();
            dt.Columns.Add("手机号");
            dt.Columns.Add("姓名");
            dt.Columns.Add("状态");
            dt.Columns.Add("上次更新时间");
            dataGridViewContacts.DataSource = dt;
            dataGridViewContacts.Columns[0].Width = 90;
            dataGridViewContacts.Columns[1].Width = 110;
            dataGridViewContacts.Columns[2].Width = 322;
            dataGridViewContacts.Columns[3].Width = 120;

            oper = new DataOperation(dt);
        }

        private void buttonLogin_Click(object sender, EventArgs e)
        {
            currentUser = new User();
            loginGuiChange(ref currentUser);
        }

        private void buttonRegister_Click(object sender, EventArgs e)
        {
            User newUser = new User();
            newUser.PhoneNum = textRegisterPhoneNum.Text;
            newUser.Name = textRegisterName.Text;
            newUser.Status = textRegisterStatus.Text;
            newUser.Codeword = textRegisterCodeword.Text;
            newUser.Connections = new List<Contact>();

            if (!oper.Register(newUser))
            {
                MessageBox.Show("注册失败！");
                return;
            }

            registerGuiChange(newUser);
            MessageBox.Show("注册成功！");
        }

        private void loginGuiChange(ref User u)
        {
            dt.Clear();

            string number = textLoginPhoneNum.Text;

            
            try
            {
                FileStream stream = new FileStream(Constants.USER_INFO_DIR + number + ".inf", FileMode.Open, FileAccess.Read);
                BinaryFormatter f = new BinaryFormatter();
                u = (User)f.Deserialize(stream);
                stream.Close();
            }
            catch (IOException)
            {   
                MessageBox.Show("本地没有该用户！");
                return;
            }
            finally
            {
            }

            labelCurrentPhoneNum.Text = u.PhoneNum;

            for (int i = 0; i < u.Connections.Count; i++)
            {
                DataRow dr = dt.NewRow();
                dr[0] = u.Connections[i].PhoneNum;
                dr[1] = u.Connections[i].Name;
                dr[2] = u.Connections[i].Status;
                dr[3] = u.Connections[i].LastUpdateTime;
                dt.Rows.Add(dr);
            }
        }

        private void registerGuiChange(User u)
        {
            FileStream stream = new FileStream(Constants.USER_INFO_DIR + u.PhoneNum + ".inf", FileMode.OpenOrCreate, FileAccess.Write);
            try
            {
                BinaryFormatter f = new BinaryFormatter();
                f.Serialize(stream, u);
            }
            catch (Exception)
            {
            }
            finally
            {
                stream.Close();
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            if (currentUser == null)
            {
                MessageBox.Show("请先登录！");
                return;
            }

            refreshConnections();

            if (currentUser.Connections.Count > 256)
                return;

            string newName = textUpdateName.Text;
            string newStatus = textUpdateStatus.Text;
            string newCodeword = textUpdateCodeword.Text;

            bool codewordChanged = ((newCodeword != "") && (!newCodeword.Equals(currentUser.Codeword)));
            
            if (newName != "")
                currentUser.Name = newName;
            if (newStatus != "")
                currentUser.Status = newStatus;
            if (newCodeword != "")
                currentUser.Codeword = newCodeword;

            oper.Update(currentUser, codewordChanged);

            labelCurrentPhoneNum.Text = currentUser.PhoneNum;
        }

        private void refreshConnections()
        {
            if (currentUser != null && currentUser.Connections != null)
            {
                currentUser.Connections.Clear();
                foreach (DataRow dr in dt.Rows)
                {
                    if (dr[0].GetType().Name.Equals("DBNull"))
                        dr[0] = "";
                    if (dr[1].GetType().Name.Equals("DBNull"))
                        dr[1] = "";
                    if (dr[2].GetType().Name.Equals("DBNull"))
                        dr[2] = "";
                    if (dr[3].GetType().Name.Equals("DBNull"))
                        dr[3] = "0";
                    currentUser.Connections.Add(new Contact((string)dr[0], (string)dr[1], (string)dr[2], int.Parse((string)dr[3])));
                }
            }
        }

        private void formClosed(object sender, FormClosedEventArgs e)
        {
            refreshConnections();
            if (currentUser == null || currentUser.PhoneNum == null)
                return;
            FileStream stream = new FileStream(Constants.USER_INFO_DIR + currentUser.PhoneNum + ".inf", FileMode.OpenOrCreate, FileAccess.Write);
            try
            {
                BinaryFormatter f = new BinaryFormatter();
                f.Serialize(stream, currentUser);
            }
            catch (Exception)
            {
            }
            finally
            {
                stream.Close();
            }
        }

        private void buttonGetinfo_Click(object sender, EventArgs e)
        {
            if (currentUser == null)
            {
                MessageBox.Show("请先登录！");
                return;
            }

            refreshConnections();

            int timestamp_now = (int)(DateTime.Now - new DateTime(1970, 1, 1)).TotalSeconds;

            if (textGetinfoTimestamp.Text == "")
            {
                MessageBox.Show("请输入时间戳！");
                return;
            }
            Int64 threshold = Int64.Parse(textGetinfoTimestamp.Text);

            List<Contact> requests = new List<Contact>();
            foreach (DataGridViewRow row in dataGridViewContacts.SelectedRows)
            {
                requests.Add(new Contact(row.Cells[0].Value.ToString(),
                    row.Cells[1].Value.ToString(), row.Cells[2].Value.ToString()));
                row.Cells[3].Value = timestamp_now.ToString();
            }

            if (requests.Count > Constants.MAX_REQ_NUM)
            {
                MessageBox.Show("每次更新的条目数不能多于16！");
                return;
            }

            oper.Getinfo(currentUser, requests, threshold);

            refreshConnections();
        }

        private void buttonCurrentUserInfo_Click(object sender, EventArgs e)
        {
            if (currentUser == null)
            {
                MessageBox.Show("请先登录！");
                return;
            }

            MessageBox.Show("手机号：      " + currentUser.PhoneNum + "\n" + 
                "名字：          " + currentUser.Name + "\n" +
                "状态：          " + currentUser.Status + "\n" +
                "Codeword：" + currentUser.Codeword);
        }
    }
}


