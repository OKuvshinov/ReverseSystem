
// ReverseWayDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CReverseWayDlg
class CReverseWayDlg : public CDialogEx
{
// Создание
public:
	CReverseWayDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REVERSEWAY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox AmountOfEqui;
	CEdit AmountOfEquals;
	afx_msg void start_input_equals();
	CEdit CertainEqual;
	afx_msg void add_equal();
	afx_msg void make_step();
	CEdit TestResult;
};
