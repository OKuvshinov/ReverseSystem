
// ReverseWayDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ReverseWay.h"
#include "ReverseWayDlg.h"
#include "afxdialogex.h"

#include "SysOfEqui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CReverseWayDlg



CReverseWayDlg::CReverseWayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REVERSEWAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReverseWayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, AmountOfEquals);
	DDX_Control(pDX, IDC_EDIT2, CertainEqual);
	DDX_Control(pDX, IDC_EDIT3, TestResult);
}

BEGIN_MESSAGE_MAP(CReverseWayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReverseWayDlg::start_input_equals)
	ON_BN_CLICKED(IDC_BUTTON2, &CReverseWayDlg::add_equal)
	ON_BN_CLICKED(IDC_BUTTON3, &CReverseWayDlg::make_step)
END_MESSAGE_MAP()


// Обработчики сообщений CReverseWayDlg

BOOL CReverseWayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CReverseWayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CReverseWayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CReverseWayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


SysOfEqui Equals;

void CReverseWayDlg::start_input_equals()
{
	CString AOE;
	AmountOfEquals.GetWindowTextW(AOE);
	if (_ttoi(AOE) > 0)
	{
		Equals.set_AOE(AOE);
		CertainEqual.EnableWindow(1);
	}
	else
	{
		AfxMessageBox(_T("Ошибка ввода!"), MB_ICONERROR);
	}
	// TODO: добавьте свой код обработчика уведомлений
}


void CReverseWayDlg::add_equal()
{
	CString InputEqual;
	CertainEqual.GetWindowTextW(InputEqual);
	int a = _ttoi(CString(InputEqual[InputEqual.GetLength() - 1]));
	if (_ttoi(CString(InputEqual[InputEqual.GetLength() - 1])) == 0 && InputEqual[InputEqual.GetLength() - 1] != '0')
	{
		AfxMessageBox(_T("Ошибка ввода!"), MB_ICONERROR);
	}
	else
	{
		Equals.add_equal(InputEqual);
	}
	// TODO: добавьте свой код обработчика уведомлений
}


void CReverseWayDlg::make_step()
{
	CString answer;
	answer.Format(_T("%.2f"), Equals.parse_from_str());
	TestResult.SetWindowTextW(answer);
	// TODO: добавьте свой код обработчика уведомлений
}
