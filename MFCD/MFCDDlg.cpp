
// MFCDDlg.cpp: 实现文件
//
#include "stdafx.h"
#include "MFCD.h"
#include "MFCDDlg.h"
#include "afxdialogex.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2\opencv.hpp>
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Mat img;    //全局原图
Mat output;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDDlg 对话框



CMFCDDlg::CMFCDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CMFCDDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BAOCUN, &CMFCDDlg::OnBnClickedBaocun)
	ON_BN_CLICKED(IDC_HD, &CMFCDDlg::OnBnClickedHd)
	ON_BN_CLICKED(IDC_BAOCUN2, &CMFCDDlg::OnBnClickedBaocun2)
	ON_BN_CLICKED(IDC_BAOCUN3, &CMFCDDlg::OnBnClickedBaocun3)
	ON_BN_CLICKED(IDC_HD5, &CMFCDDlg::OnBnClickedHd5)
	ON_BN_CLICKED(IDC_HD6, &CMFCDDlg::OnBnClickedHd6)
	ON_BN_CLICKED(IDC_HD2, &CMFCDDlg::OnBnClickedHd2)
	ON_BN_CLICKED(IDC_HD4, &CMFCDDlg::OnBnClickedHd4)
	ON_BN_CLICKED(IDC_HD3, &CMFCDDlg::OnBnClickedHd3)
	ON_BN_CLICKED(IDC_HD7, &CMFCDDlg::OnBnClickedHd7)
END_MESSAGE_MAP()


// CMFCDDlg 消息处理程序

BOOL CMFCDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCDDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL,
		OPEN_EXISTING | OFN_FILEMUSTEXIST, //路径必须存在，文件必须存在
		_T("*png(*.png)|(*.png)|所有文件(*.*)|*.*||"),
		this);
	dlg.DoModal();

		USES_CONVERSION;
		CString str = dlg.GetPathName();
		cv::String cvStr = W2A(str);
		   // 读入一张图,RGB形式加载   
		   img = imread(cvStr,1);
		   // 在窗口中显示图片   
		   if (img.empty())
		   {
			   return ;
		   }
		   //namedWindow("图像编辑", WINDOW_AUTOSIZE);
		   imshow("图像编辑",img);
		   waitKey(0);
	
	
}


void CMFCDDlg::OnBnClickedBaocun()
{
	// TODO: 在此添加控件通知处理程序代码
	    CFileDialog dlg(FALSE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		_T("所有文件|*.*||"), this);
	   dlg.DoModal();
	   USES_CONVERSION;
	   CString str = dlg.GetPathName();
	   cv::String cvStr = W2A(str);
	   imwrite(cvStr, output);

	 
}

//灰度图像
void CMFCDDlg::OnBnClickedHd()
{
	// TODO: 在此添加控件通知处理程序代码
	//先有RGB图转为灰度图像
	int Len = img.channels();
	if (Len == 3)
	{
		cv::cvtColor(img, img, COLOR_BGR2GRAY);
	}
	imshow("图像编辑", img);
	waitKey(0);

}

//反色
void CMFCDDlg::OnBnClickedBaocun2()
{
	int Len = img.channels();
	if (Len == 3)
	{
		cv::cvtColor(img, img, COLOR_BGR2GRAY);
	}
	// TODO: 在此添加控件通知处理程序代码
	int height = img.rows;  //高度
	int width = img.cols;   //宽度
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			//获取了像素值,反差法
			int gray = img.at<uchar>(row, col);
			img.at<uchar>(row,col)=255 - gray;
		}
	}
	 
	imshow("图像编辑", img);
	waitKey(0);
}


void CMFCDDlg::OnBnClickedBaocun3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (img.empty())
	{
		return;
	}
	int Len = img.channels();
	if (Len == 3)
	{
		cv::cvtColor(img,img, COLOR_BGR2GRAY);
	}
	int height = img.rows; //行,高
	int width = img.cols; //列，宽
	int gray;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			gray = img.at<uchar>(row, col);
			if (gray > 127)
				img.at<uchar>(row, col) = 255;
			else
			{
				img.at<uchar>(row, col) = 0;
			}
		}
	}
	imshow("图像编辑", img);
	waitKey(0);
}


void CMFCDDlg::OnBnClickedHd5()
{
	// TODO: 在此添加控件通知处理程序代码
		
		flip(img, img, 1);
		imshow("图像编辑", img);
		waitKey(0);

}


void CMFCDDlg::OnBnClickedHd6()
{
	// TODO: 在此添加控件通知处理程序代码
	flip(img, img, 0);
	imshow("图像编辑", img);
	waitKey(0);
}


void CMFCDDlg::OnBnClickedHd2()
{

	Mat t, f;
	transpose(img, t);
	flip(t, img, 1); // code = 0 - x axis; 1 - y ; -1 - both
	imshow("图像编辑", img);
	waitKey(0);
}


void CMFCDDlg::OnBnClickedHd4()
{
	// TODO: 在此添加控件通知处理程序代码
	//0: 沿X轴翻转； >0: 沿Y轴翻转； <0: 沿X轴和Y轴翻转
	flip(img, img, 0);// 翻转模式，flipCode == 0垂直翻转（沿X轴翻转），flipCode>0水平翻转（沿Y轴翻转），flipCode<0水平垂直翻转（先沿X轴翻转，再沿Y轴翻转，等价于旋转180°）
	flip(img, img, 1);
	imshow("图像编辑", img);
}


void CMFCDDlg::OnBnClickedHd3()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat t, f;
	transpose(img, t);
	flip(t, img, 0); // code = 0 - x axis; 1 - y ; -1 - both
	imshow("图像编辑", img);
	waitKey(0);

}


void CMFCDDlg::OnBnClickedHd7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (img.empty())
	{
		return;
	}
	int i = 600;   //雪点数

	for (int k = 0; k < i; k++)
	{
		int i = rand() % img.cols;
		int j = rand() % img.rows;
		if (img.channels() == 1) //核实通道数
		{
			img.at<uchar>(j, i) = 255;
			if (i < (int)img.cols)
				img.at<uchar>(j + 1, i) = 255;
			if (j < (int)img.rows)
				img.at<uchar>(j, i + 1) = 255;
			if (i < (int)img.cols && j < (int)img.rows)
				img.at<uchar>(j + 1, i + 1) = 255;
		}
		else if (img.channels() == 3)
		{
			img.at<cv::Vec3b>(j, i)[0] = 255;
			img.at<cv::Vec3b>(j, i)[1] = 255;
			img.at<cv::Vec3b>(j, i)[2] = 255;
			if (i < (int)img.cols - 1)
			{
				img.at<cv::Vec3b>(j, i + 1)[0] = 255;
				img.at<cv::Vec3b>(j, i + 1)[1] = 255;
				img.at<cv::Vec3b>(j, i + 1)[2] = 255;
			}
			if (j < (int)img.rows - 1)
			{
				img.at<cv::Vec3b>(j + 1, i)[0] = 255;
				img.at<cv::Vec3b>(j + 1, i)[1] = 255;
				img.at<cv::Vec3b>(j + 1, i)[2] = 255;
			}
			if (j < (int)img.rows - 1 && i < (int)img.cols - 1)
			{
				img.at<cv::Vec3b>(j + 1, i + 1)[0] = 255;
				img.at<cv::Vec3b>(j + 1, i + 1)[1] = 255;
				img.at<cv::Vec3b>(j + 1, i + 1)[2] = 255;
			}
		}
	}
	imshow("图像编辑", img);
	waitKey(0);
}
