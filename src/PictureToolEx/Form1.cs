using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Imaging;
using System.Collections;
using System.Threading;

namespace PictureToolEx
{
    public partial class Form1 : Form
    {
        //锁
        object locker = new object(); 

        //正在合成的文件名-用于显示
        static private string _file = "";

        //进度条
        private int _range = 0;
        private int _value = 0;
        
        //是否转换完成
        private bool _isok = false;

        //源和目标目录
        private string _direct = "";
        private string _savePath = "";

        //保存合成上下文（合成的张数，yy
        private int _count = 0;
        private string _strPrefix = "";
        private ArrayList list = new ArrayList();

        //合成总张数
        private int _countDst = 0;

        public Form1()
        {
            InitializeComponent();
        }

        //来源目录
        private void button1_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folderDlg = new FolderBrowserDialog();
            folderDlg.ShowDialog();
            textBox1.Text = folderDlg.SelectedPath;
        }

        //保存目录
        private void button2_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folderDlg = new FolderBrowserDialog();
            folderDlg.ShowDialog();

            //提取时间
            string str = textBox1.Text;
            str = str.Substring(str.LastIndexOf('\\'));

            str = str + "-new";

            textBox2.Text = folderDlg.SelectedPath + str;
        }

        //开始转换按钮
        private void button3_Click(object sender, EventArgs e)
        {
            _countDst = 0;

            _file = textBox1.Text;
            _direct = comboBox1.Text;
            _savePath = textBox2.Text;
            if (_file.Length < 2 || _direct.Length < 2)
            {
                lblMsg.Text = "请正确填写来源目录和保存目录!";
                return;
            }

            if (!Directory.Exists(_savePath))
            {
                Directory.CreateDirectory(_savePath);   
            }

            lblMsg.Text = "开始转换,请稍候...";
            ShowUI(false);


            ParameterizedThreadStart ParStart = new ParameterizedThreadStart(StartChange);
            Thread t = new Thread(ParStart);

            _isok = false;
            _range = 0;
            _value = 0;

            //传递参数
            t.Start(this);

            while (_range == 0)
            {
                Thread.Sleep(10);
            }

            progressBar1.Maximum = _range;
            while (!_isok)
            {
                progressBar1.Value = _value;
                Monitor.Enter(locker);
                lblMsg.Text = _file;
                Thread.Sleep(10);
                Monitor.Exit(locker);
                Application.DoEvents();
            }
            progressBar1.Value = _range;
            Thread.Sleep(100);

            lblMsg.Text = "成功完成转换!\r\n    合成总张数:" + _countDst.ToString();
            ShowUI(true);
        }

        private void ShowUI(bool bShow)
        {
            textBox1.Enabled = bShow;
            textBox2.Enabled = bShow;
            comboBox1.Enabled = bShow;
            button1.Enabled = bShow;
            button2.Enabled = bShow;
            button3.Enabled = bShow;
        }

        //线程函数
        static void StartChange(object ParObject)
        {
            //传递参数
            Form1 form = (Form1)ParObject;

            form.ListFiles(new DirectoryInfo(_file));
        }

        public void ListFiles(FileSystemInfo info)
        {
            if (!info.Exists)
                return;

            DirectoryInfo TheFolder = info as DirectoryInfo;
            //不是目录返回
            if (TheFolder == null)
                return;

            FileSystemInfo[] files = TheFolder.GetFileSystemInfos();
            for (int i = 0; i < files.Length; ++i )
            {
                _range = files.Length;
                FileInfo fi = files[i] as FileInfo;
                //是文件
                if (fi != null)
                {
                    string str = fi.Name;
                    str = str.Substring(0, str.Length - 6);

                    if (_strPrefix != str && _count == 0)
                    {
                        _strPrefix = str;
                        _count++;
                    }
                    else if (_strPrefix != str)
                    {
                        if(_count == 2)
                        {
                            string strSavePath = CreateNewFileName(_strPrefix);

                            ComposeTowPictures(list[0].ToString(), list[1].ToString(), strSavePath);
                            _countDst++;
                        }
                        else if(_count == 3)
                        {
                            string strSavePath = CreateNewFileName(_strPrefix); 
                            ComposeThreePictures(list[0].ToString(), list[1].ToString(), list[2].ToString(), strSavePath);
                            _countDst++;
                        }
                        list.Clear();
                        _strPrefix = str;
                        _count = 1;
                    }
                    else
                    {
                        _count++;
                    }

                    list.Add(fi.FullName);
                    _value += 1;
                }
                else
                {
                    ListFiles(files[i]);
                }
            }
            _value = _range;
            _isok = true;
        }

        //机号824车道A12014年06月03日16时43分17秒R000D0F2T标准车牌C蓝底白字P       驶向南至北违章超速时速133公里车体未知.jpg
        private string CreateNewFileName(string strPrefix)
        {
            string[] strNames = strPrefix.Split('_');

            string str;
            str = "机号" + strNames[3] + "车道A1" + GetDataTimeString(strNames[0], strNames[1]) + "R000D0F" + _count.ToString() 
                + "T标准车牌C蓝底白字P" + ((strNames[2].Length > 0) ? strNames[2] : "       ") 
                + "驶向" + _direct + "违章超速时速" + strNames[4] + "公里车体未知.jpg";

             Monitor.Enter(locker);
             _file = "正在合成:\r\n    [" + str + "]";
             Monitor.Exit(locker);

            str = _savePath + "\\" + str;

            return str;
        }

        //合成时间串
        private string GetDataTimeString(string strData, string strTime)
        {
            string strRlt;
            strRlt = strData.Substring(0, 4) + "年" + strData.Substring(4, 2) + "月" + strData.Substring(6, 2) + "日"
                + strTime.Substring(0,2) + "时" + strTime.Substring(2, 2) + "分" + strTime.Substring(4, 2) + "秒";
            return strRlt;
        }


        /// <summary>
        /// 合成两张图片
        /// </summary>
        /// <param name="strImg1">第一张图的路径</param>
        /// <param name="strImg2">第一张图的路径</param>
        /// <param name="strDst">存储路径</param>
        private void ComposeTowPictures(string strImg1, string strImg2, string strDst)
        {
            Image img1 = Image.FromFile(strImg1);
            Image img2 = Image.FromFile(strImg2);
            Image imgT = ComposeTowPictures(img1, img2, strDst);

            //释放资源，否则会报"参数无效"
            img1.Dispose();
            img2.Dispose();
            imgT.Dispose();
        }

        /// <summary>
        /// 合成3张图片
        /// </summary>
        /// <param name="strImg1"></param>
        /// <param name="strImg2"></param>
        /// <param name="strImg3"></param>
        /// <param name="strDst"></param>
        private void ComposeThreePictures(string strImg1, string strImg2, string strImg3, string strDst)
        {
            Image img1 = Image.FromFile(strImg1);
            Image img2 = Image.FromFile(strImg2);
            Image imgT = ComposeTowPictures(img1, img2, strDst);
            
            Image img3 = Image.FromFile(strImg3);
            Image imgT3 = ComposeTowPictures(imgT, img3, strDst);

            img1.Dispose();
            img2.Dispose();
            imgT.Dispose();
            img3.Dispose();
            imgT3.Dispose();
        }

        private Image ComposeTowPictures(Image img1, Image img2, string strDst)
        {
            Bitmap newImg = new Bitmap(img1.Width + img2.Width, (img1.Height > img2.Height) ? img1.Height : img2.Height);
            Graphics g = Graphics.FromImage(newImg);
            g.Clear(Color.Blue);
            g.DrawImageUnscaled(img1, 0, 0);
            g.DrawImageUnscaled(img2, img1.Width, 0);

            newImg.Save(strDst, ImageFormat.Jpeg);

            g.Dispose();
           
            return newImg;
        }


    }
}
