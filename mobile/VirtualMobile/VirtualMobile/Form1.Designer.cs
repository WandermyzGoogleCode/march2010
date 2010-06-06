namespace VirtualMobile
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxRegister = new System.Windows.Forms.GroupBox();
            this.buttonRegister = new System.Windows.Forms.Button();
            this.textRegisterCodeword = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textRegisterStatus = new System.Windows.Forms.TextBox();
            this.textRegisterName = new System.Windows.Forms.TextBox();
            this.textRegisterPhoneNum = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBoxUpdate = new System.Windows.Forms.GroupBox();
            this.textUpdateCodeword = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.buttonUpdate = new System.Windows.Forms.Button();
            this.textUpdateStatus = new System.Windows.Forms.TextBox();
            this.textUpdateName = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.buttonGetinfo = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.labelCurrentPhoneNum = new System.Windows.Forms.Label();
            this.groupBoxContacts = new System.Windows.Forms.GroupBox();
            this.textGetinfoTimestamp = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.dataGridViewContacts = new System.Windows.Forms.DataGridView();
            this.label13 = new System.Windows.Forms.Label();
            this.textLoginPhoneNum = new System.Windows.Forms.TextBox();
            this.buttonLogin = new System.Windows.Forms.Button();
            this.buttonCurrentUserInfo = new System.Windows.Forms.Button();
            this.groupBoxRegister.SuspendLayout();
            this.groupBoxUpdate.SuspendLayout();
            this.groupBoxContacts.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewContacts)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxRegister
            // 
            this.groupBoxRegister.Controls.Add(this.buttonRegister);
            this.groupBoxRegister.Controls.Add(this.textRegisterCodeword);
            this.groupBoxRegister.Controls.Add(this.label4);
            this.groupBoxRegister.Controls.Add(this.textRegisterStatus);
            this.groupBoxRegister.Controls.Add(this.textRegisterName);
            this.groupBoxRegister.Controls.Add(this.textRegisterPhoneNum);
            this.groupBoxRegister.Controls.Add(this.label3);
            this.groupBoxRegister.Controls.Add(this.label2);
            this.groupBoxRegister.Controls.Add(this.label1);
            this.groupBoxRegister.Location = new System.Drawing.Point(28, 50);
            this.groupBoxRegister.Name = "groupBoxRegister";
            this.groupBoxRegister.Size = new System.Drawing.Size(322, 297);
            this.groupBoxRegister.TabIndex = 2;
            this.groupBoxRegister.TabStop = false;
            this.groupBoxRegister.Text = "注册";
            // 
            // buttonRegister
            // 
            this.buttonRegister.Location = new System.Drawing.Point(117, 255);
            this.buttonRegister.Name = "buttonRegister";
            this.buttonRegister.Size = new System.Drawing.Size(75, 23);
            this.buttonRegister.TabIndex = 5;
            this.buttonRegister.Text = "注册";
            this.buttonRegister.UseVisualStyleBackColor = true;
            this.buttonRegister.Click += new System.EventHandler(this.buttonRegister_Click);
            // 
            // textRegisterCodeword
            // 
            this.textRegisterCodeword.Location = new System.Drawing.Point(84, 215);
            this.textRegisterCodeword.Name = "textRegisterCodeword";
            this.textRegisterCodeword.Size = new System.Drawing.Size(220, 20);
            this.textRegisterCodeword.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 218);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(55, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Codeword";
            // 
            // textRegisterStatus
            // 
            this.textRegisterStatus.Location = new System.Drawing.Point(84, 86);
            this.textRegisterStatus.Multiline = true;
            this.textRegisterStatus.Name = "textRegisterStatus";
            this.textRegisterStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textRegisterStatus.Size = new System.Drawing.Size(220, 113);
            this.textRegisterStatus.TabIndex = 3;
            // 
            // textRegisterName
            // 
            this.textRegisterName.Location = new System.Drawing.Point(84, 55);
            this.textRegisterName.Name = "textRegisterName";
            this.textRegisterName.Size = new System.Drawing.Size(220, 20);
            this.textRegisterName.TabIndex = 2;
            // 
            // textRegisterPhoneNum
            // 
            this.textRegisterPhoneNum.Location = new System.Drawing.Point(84, 26);
            this.textRegisterPhoneNum.Name = "textRegisterPhoneNum";
            this.textRegisterPhoneNum.Size = new System.Drawing.Size(220, 20);
            this.textRegisterPhoneNum.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "状态";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(31, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "姓名";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "手机号";
            // 
            // groupBoxUpdate
            // 
            this.groupBoxUpdate.Controls.Add(this.textUpdateCodeword);
            this.groupBoxUpdate.Controls.Add(this.label5);
            this.groupBoxUpdate.Controls.Add(this.buttonUpdate);
            this.groupBoxUpdate.Controls.Add(this.textUpdateStatus);
            this.groupBoxUpdate.Controls.Add(this.textUpdateName);
            this.groupBoxUpdate.Controls.Add(this.label7);
            this.groupBoxUpdate.Controls.Add(this.label6);
            this.groupBoxUpdate.Location = new System.Drawing.Point(382, 50);
            this.groupBoxUpdate.Name = "groupBoxUpdate";
            this.groupBoxUpdate.Size = new System.Drawing.Size(364, 297);
            this.groupBoxUpdate.TabIndex = 3;
            this.groupBoxUpdate.TabStop = false;
            this.groupBoxUpdate.Text = "更新个人信息";
            // 
            // textUpdateCodeword
            // 
            this.textUpdateCodeword.Location = new System.Drawing.Point(99, 215);
            this.textUpdateCodeword.Name = "textUpdateCodeword";
            this.textUpdateCodeword.Size = new System.Drawing.Size(251, 20);
            this.textUpdateCodeword.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 218);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "新Codeword";
            // 
            // buttonUpdate
            // 
            this.buttonUpdate.Location = new System.Drawing.Point(146, 255);
            this.buttonUpdate.Name = "buttonUpdate";
            this.buttonUpdate.Size = new System.Drawing.Size(75, 23);
            this.buttonUpdate.TabIndex = 4;
            this.buttonUpdate.Text = "更新";
            this.buttonUpdate.UseVisualStyleBackColor = true;
            this.buttonUpdate.Click += new System.EventHandler(this.buttonUpdate_Click);
            // 
            // textUpdateStatus
            // 
            this.textUpdateStatus.Location = new System.Drawing.Point(99, 55);
            this.textUpdateStatus.Multiline = true;
            this.textUpdateStatus.Name = "textUpdateStatus";
            this.textUpdateStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textUpdateStatus.Size = new System.Drawing.Size(251, 144);
            this.textUpdateStatus.TabIndex = 1;
            // 
            // textUpdateName
            // 
            this.textUpdateName.Location = new System.Drawing.Point(99, 26);
            this.textUpdateName.Name = "textUpdateName";
            this.textUpdateName.Size = new System.Drawing.Size(251, 20);
            this.textUpdateName.TabIndex = 0;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(18, 58);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(43, 13);
            this.label7.TabIndex = 2;
            this.label7.Text = "新状态";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(18, 29);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(43, 13);
            this.label6.TabIndex = 1;
            this.label6.Text = "新姓名";
            // 
            // buttonGetinfo
            // 
            this.buttonGetinfo.Location = new System.Drawing.Point(262, 19);
            this.buttonGetinfo.Name = "buttonGetinfo";
            this.buttonGetinfo.Size = new System.Drawing.Size(116, 23);
            this.buttonGetinfo.TabIndex = 3;
            this.buttonGetinfo.Text = "获取所选项信息";
            this.buttonGetinfo.UseVisualStyleBackColor = true;
            this.buttonGetinfo.Click += new System.EventHandler(this.buttonGetinfo_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(25, 13);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(67, 13);
            this.label10.TabIndex = 3;
            this.label10.Text = "当前用户：";
            this.label10.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // labelCurrentPhoneNum
            // 
            this.labelCurrentPhoneNum.AutoSize = true;
            this.labelCurrentPhoneNum.Location = new System.Drawing.Point(98, 13);
            this.labelCurrentPhoneNum.Name = "labelCurrentPhoneNum";
            this.labelCurrentPhoneNum.Size = new System.Drawing.Size(43, 13);
            this.labelCurrentPhoneNum.TabIndex = 5;
            this.labelCurrentPhoneNum.Text = "未登录";
            // 
            // groupBoxContacts
            // 
            this.groupBoxContacts.Controls.Add(this.textGetinfoTimestamp);
            this.groupBoxContacts.Controls.Add(this.label8);
            this.groupBoxContacts.Controls.Add(this.buttonGetinfo);
            this.groupBoxContacts.Controls.Add(this.dataGridViewContacts);
            this.groupBoxContacts.Location = new System.Drawing.Point(28, 368);
            this.groupBoxContacts.Name = "groupBoxContacts";
            this.groupBoxContacts.Size = new System.Drawing.Size(718, 342);
            this.groupBoxContacts.TabIndex = 11;
            this.groupBoxContacts.TabStop = false;
            this.groupBoxContacts.Text = "通讯录";
            // 
            // textGetinfoTimestamp
            // 
            this.textGetinfoTimestamp.Location = new System.Drawing.Point(79, 21);
            this.textGetinfoTimestamp.Name = "textGetinfoTimestamp";
            this.textGetinfoTimestamp.Size = new System.Drawing.Size(167, 20);
            this.textGetinfoTimestamp.TabIndex = 5;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(18, 24);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 13);
            this.label8.TabIndex = 4;
            this.label8.Text = "时间戳：";
            // 
            // dataGridViewContacts
            // 
            this.dataGridViewContacts.AllowUserToResizeRows = false;
            this.dataGridViewContacts.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewContacts.Location = new System.Drawing.Point(21, 49);
            this.dataGridViewContacts.Name = "dataGridViewContacts";
            this.dataGridViewContacts.Size = new System.Drawing.Size(685, 287);
            this.dataGridViewContacts.TabIndex = 0;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(412, 13);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(55, 13);
            this.label13.TabIndex = 8;
            this.label13.Text = "手机号：";
            // 
            // textLoginPhoneNum
            // 
            this.textLoginPhoneNum.Location = new System.Drawing.Point(481, 10);
            this.textLoginPhoneNum.Name = "textLoginPhoneNum";
            this.textLoginPhoneNum.Size = new System.Drawing.Size(169, 20);
            this.textLoginPhoneNum.TabIndex = 0;
            // 
            // buttonLogin
            // 
            this.buttonLogin.Location = new System.Drawing.Point(671, 8);
            this.buttonLogin.Name = "buttonLogin";
            this.buttonLogin.Size = new System.Drawing.Size(75, 23);
            this.buttonLogin.TabIndex = 1;
            this.buttonLogin.Text = "登录";
            this.buttonLogin.UseVisualStyleBackColor = true;
            this.buttonLogin.Click += new System.EventHandler(this.buttonLogin_Click);
            // 
            // buttonCurrentUserInfo
            // 
            this.buttonCurrentUserInfo.Location = new System.Drawing.Point(207, 8);
            this.buttonCurrentUserInfo.Name = "buttonCurrentUserInfo";
            this.buttonCurrentUserInfo.Size = new System.Drawing.Size(87, 23);
            this.buttonCurrentUserInfo.TabIndex = 12;
            this.buttonCurrentUserInfo.Text = "当前用户信息";
            this.buttonCurrentUserInfo.UseVisualStyleBackColor = true;
            this.buttonCurrentUserInfo.Click += new System.EventHandler(this.buttonCurrentUserInfo_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 722);
            this.Controls.Add(this.buttonCurrentUserInfo);
            this.Controls.Add(this.buttonLogin);
            this.Controls.Add(this.textLoginPhoneNum);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.groupBoxContacts);
            this.Controls.Add(this.labelCurrentPhoneNum);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.groupBoxUpdate);
            this.Controls.Add(this.groupBoxRegister);
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.Text = "Virtual Mobile Phone";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formClosed);
            this.groupBoxRegister.ResumeLayout(false);
            this.groupBoxRegister.PerformLayout();
            this.groupBoxUpdate.ResumeLayout(false);
            this.groupBoxUpdate.PerformLayout();
            this.groupBoxContacts.ResumeLayout(false);
            this.groupBoxContacts.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewContacts)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxRegister;
        private System.Windows.Forms.GroupBox groupBoxUpdate;
        private System.Windows.Forms.TextBox textRegisterStatus;
        private System.Windows.Forms.TextBox textRegisterName;
        private System.Windows.Forms.TextBox textRegisterPhoneNum;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textRegisterCodeword;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textUpdateStatus;
        private System.Windows.Forms.TextBox textUpdateName;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button buttonRegister;
        private System.Windows.Forms.Button buttonUpdate;
        private System.Windows.Forms.Button buttonGetinfo;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label labelCurrentPhoneNum;
        private System.Windows.Forms.TextBox textUpdateCodeword;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox groupBoxContacts;
        private System.Windows.Forms.DataGridView dataGridViewContacts;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textLoginPhoneNum;
        private System.Windows.Forms.Button buttonLogin;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textGetinfoTimestamp;
        private System.Windows.Forms.Button buttonCurrentUserInfo;
    }
}

