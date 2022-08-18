
// CalculatorDlg.h : header file
//

#pragma once
#include "Calculator.h"

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	CFont m_font;
	CFont m_historyFont;
	CString m_history;
	CString m_result;
	CEdit m_edit_history;
	CEdit m_edit_result;
	CButton m_button_equal;
	CButton m_button_0;
	CButton m_button_1;
	CButton m_button_2;
	CButton m_button_3;
	CButton m_button_4;
	CButton m_button_5;
	CButton m_button_6;
	CButton m_button_7;
	CButton m_button_8;
	CButton m_button_9;
	CButton m_button_dos;
	CButton m_button_del;
	CButton m_button_ac;
	CButton m_button_mul;
	CButton m_button_div;
	CButton m_button_plus;
	CButton m_button_sub;
public:
	afx_msg void OnEnChangeEditHistory();
	afx_msg void OnEnChangeEditResult();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonAc();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonDos();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	Calculator m_calculator;
	CString m_out;
	bool m_firstDigitEntered = FALSE;
	bool m_errorInput = false;
	const CString m_outputReset{ "0" };

	void resetOutput();
	void reset();
	void addSymbol(char digit);
	void delText();
	void doOperation(Calculator::ActionType operation, bool handleNumber = true);
	void createHistoryText();
};