
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HISTORY, m_edit_history);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_edit_result);
	DDX_Text(pDX, IDC_EDIT_HISTORY, m_history);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_result);
	DDX_Control(pDX, IDC_BUTTON_DOS, m_button_dos);
	DDX_Control(pDX, IDC_BUTTON_0, m_button_0);
	DDX_Control(pDX, IDC_BUTTON_1, m_button_1);
	DDX_Control(pDX, IDC_BUTTON_2, m_button_2);
	DDX_Control(pDX, IDC_BUTTON_3, m_button_3);
	DDX_Control(pDX, IDC_BUTTON_4, m_button_4);
	DDX_Control(pDX, IDC_BUTTON_5, m_button_5);
	DDX_Control(pDX, IDC_BUTTON_6, m_button_6);
	DDX_Control(pDX, IDC_BUTTON_7, m_button_7);
	DDX_Control(pDX, IDC_BUTTON_8, m_button_8);
	DDX_Control(pDX, IDC_BUTTON_9, m_button_9);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_button_del);
	DDX_Control(pDX, IDC_BUTTON_AC, m_button_ac);
	DDX_Control(pDX, IDC_BUTTON_MUL, m_button_mul);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_button_del);
	DDX_Control(pDX, IDC_BUTTON_AC, m_button_ac);
	DDX_Control(pDX, IDC_BUTTON_MUL, m_button_mul);
	DDX_Control(pDX, IDC_BUTTON_DIV, m_button_div);
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_button_plus);
	DDX_Control(pDX, IDC_BUTTON_SUB, m_button_sub);
	DDX_Control(pDX, IDC_BUTTON_EQUAL, m_button_equal);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_HISTORY, &CCalculatorDlg::OnEnChangeEditHistory)
	ON_EN_CHANGE(IDC_EDIT_RESULT, &CCalculatorDlg::OnEnChangeEditResult)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CCalculatorDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_AC, &CCalculatorDlg::OnBnClickedButtonAc)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalculatorDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_DOS, &CCalculatorDlg::OnBnClickedButtonDos)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_font.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Algerian"));
	m_historyFont.CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Algerian"));
	m_edit_result.SetFont(&m_font);
	m_button_0.SetFont(&m_font);
	m_button_1.SetFont(&m_font);
	m_button_2.SetFont(&m_font);
	m_button_3.SetFont(&m_font);
	m_button_4.SetFont(&m_font);
	m_button_5.SetFont(&m_font);
	m_button_6.SetFont(&m_font);
	m_button_7.SetFont(&m_font);
	m_button_8.SetFont(&m_font);
	m_button_9.SetFont(&m_font);
	m_button_plus.SetFont(&m_font);
	m_button_ac.SetFont(&m_font);
	m_button_sub.SetFont(&m_font);
	m_button_mul.SetFont(&m_font);
	m_edit_history.SetFont(&m_historyFont);
	m_button_div.SetFont(&m_font);
	m_button_equal.SetFont(&m_font);
	m_button_del.SetFont(&m_font);

	GetDlgItem(IDC_EDIT_RESULT)->SetFont(&m_historyFont);
	GetDlgItem(IDC_EDIT_HISTORY)->SetFont(&m_historyFont);
	m_result = "0";
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCalculatorDlg::OnEnChangeEditHistory()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCalculatorDlg::OnEnChangeEditResult()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedButtonEqual()
{
	doOperation(Calculator::ActionType::Equals);
}


void CCalculatorDlg::OnBnClickedButtonDel()
{
	addSymbol('d');
}


void CCalculatorDlg::OnBnClickedButtonAc()
{
	reset();
}


void CCalculatorDlg::OnBnClickedButtonPlus()
{
	doOperation(Calculator::ActionType::Plus);
}


void CCalculatorDlg::OnBnClickedButtonSub()
{
	doOperation(Calculator::ActionType::Minus);
}


void CCalculatorDlg::OnBnClickedButtonMul()
{
	doOperation(Calculator::ActionType::Multiply);
}


void CCalculatorDlg::OnBnClickedButtonDiv()
{
	doOperation(Calculator::ActionType::Divide);
}


void CCalculatorDlg::OnBnClickedButtonDos()
{
	addSymbol('.');
}


void CCalculatorDlg::OnBnClickedButton0()
{
	addSymbol('0');
}


void CCalculatorDlg::OnBnClickedButton1()
{
	addSymbol('1');
}


void CCalculatorDlg::OnBnClickedButton2()
{
	addSymbol('2');
}


void CCalculatorDlg::OnBnClickedButton3()
{
	addSymbol('3');
}


void CCalculatorDlg::OnBnClickedButton4()
{
	addSymbol('4');
}


void CCalculatorDlg::OnBnClickedButton5()
{
	addSymbol('5');
}


void CCalculatorDlg::OnBnClickedButton6()
{
	addSymbol('6');
}


void CCalculatorDlg::OnBnClickedButton7()
{
	addSymbol('7');
}


void CCalculatorDlg::OnBnClickedButton8()
{
	addSymbol('8');
}


void CCalculatorDlg::OnBnClickedButton9()
{
	addSymbol('9');
}

HBRUSH CCalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (nCtlColor) {
	case CTLCOLOR_EDIT:
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_HISTORY || pWnd->GetDlgCtrlID() == IDC_EDIT_RESULT)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
			return (HBRUSH)GetStockObject(WHITE_BRUSH);
		}
	}
	// TODO:  Return a different brush if the default is not desired
	// return hbr;
	return (HBRUSH)GetStockObject(BLACK_BRUSH);
}

void CCalculatorDlg::reset()
{
	m_calculator.reset();
	m_errorInput = false;
	m_firstDigitEntered = FALSE;
	resetOutput();
	m_history = "";
	m_result = m_outputReset;
	UpdateData(FALSE);
}

void CCalculatorDlg::resetOutput()
{
	m_out = m_outputReset;
}

void CCalculatorDlg::delText()
{
	if (m_history[m_history.GetLength() - 1] != '=')
	{
		if (m_calculator.isOperation(m_calculator.getLastInput().actionType)) {
			m_out.Delete(m_out.GetLength() - 1);
			m_history.Delete(m_history.GetLength() - 1);
			if (m_firstDigitEntered) {
				UpdateData(FALSE);
				return;
			}
			Calculator::Action input;
			if (m_calculator.getLastInput().actionType == Calculator::ActionType::Number && m_out != "")
			{
				input.actionType = Calculator::ActionType::Number;
				input.value = _wtof(m_out);
			}
			else
				input.actionType = Calculator::ActionType::None;
			m_calculator.deleteLastAction(input);
		}
		UpdateData(FALSE);
	}
}

void CCalculatorDlg::addSymbol(char digit)
{
	if (m_errorInput)	// neu m_errorInput = true thi return
		return;

	UpdateData();
	// After an operation the next digit will always be the first digit of the next number.
	// This check can only be done for the first digit, so if we are entering digits
	// after first digit this check is ignored (m_firstDigitEntered==TRUE).
	if (digit == 'd')
	{
		delText();
		return;
	} 
	else 
		m_history += digit;
	UpdateData(FALSE);
	if (m_calculator.isOperation(m_calculator.getLastInput().actionType) && !m_firstDigitEntered)
	{
		// (3 + 4 x 6 = input: 2 => 2)
		m_out = digit;
	}
	else
	{
		if (m_out == m_outputReset && digit == '0' || m_out == m_outputReset && digit == '.')
			return; // (0 : input: 0 => 0) if zero is the first digit typed, ignore it
		else if (m_out == m_outputReset)
			m_out = digit; // (0 : input: 6 => 6) first digit
		else
			m_out += digit; // (45 : input: 9 => 459)
	}
	// a valid digit was added
	m_firstDigitEntered = TRUE;
	
	UpdateData(FALSE);
}

void CCalculatorDlg::createHistoryText()
{
	m_history = "";
	int historySize = m_calculator.getActionsSize();
	for (int i = 0; i < historySize; ++i)
	{
		switch (m_calculator.getAction(i).actionType)
		{
		case Calculator::ActionType::Number:
		{
			CString strNumber;
			std::stringstream ss;
			ss << m_calculator.getAction(i).value;
			std::string stdNum = ss.str();

			strNumber = stdNum.c_str();
			if (m_history.IsEmpty())
				m_history += strNumber;
			else
				m_history += (CString(" ") + strNumber);
		}
		break;
		case Calculator::ActionType::Plus:
			m_history += " +";
			break;
		case Calculator::ActionType::Divide:
			m_history += " /";
			break;
		case Calculator::ActionType::Minus:
			m_history += " -";
			break;
		case Calculator::ActionType::Multiply:
			m_history += " x";
			break;
		case Calculator::ActionType::Equals:
			m_history +=" =";
			break;
		case Calculator::ActionType::None:
			break;
		}
	}
}

// if handleNumber == true then first handles the number entered in the output
// window before doing the operation.
void CCalculatorDlg::doOperation(Calculator::ActionType operation, bool handleNumber)
{
	if (m_errorInput)
		return;
	UpdateData();
	Calculator::Action input;
	if (handleNumber)
	{
		// first add the last entered number
		input.actionType = Calculator::ActionType::Number;
		input.value = _wtof(m_out);
		m_calculator.addInput(input);
	}
	// then add the (last) operation
	input.actionType = operation;
	m_errorInput = false;
	try
	{
		// After a (valid) operation we always print a current result if
		// there is something to print currently. This is the case with all the current 
		// operations. Later on if there is different kind of operation which does not
		// behave like this, then a new code is needed here for that operation.
		if (m_calculator.addInput(input))
		{
			// The only situation we will not print the total result here is if both term and 
			// expression have values currently (are "in use"). For example: "3 + 5 /", 
			// => operation == Divide and we would not like to print the total result of
			// this yet becouse that would be 3; we want to wait until the term part (5 / ...)
			// is finished, then we will print the total 3 + ... .
			if (!m_calculator.hasLeftTermValue() || !m_calculator.hasLeftExpressionValue())
			{
				// print the current total value
				std::stringstream ss;
				ss << m_calculator.getCurrentResult();
				std::string curResult = ss.str();
				m_out = "";
				m_out += curResult.c_str();
				UpdateData(FALSE);
			}
		}
		else // this should never happen; coming here means possible an error in the code
			AfxMessageBox(_T("Error: An unknown operation."));
	}
	catch (std::exception& e)
	{
		// note: the user can only continue after "divided by zero" error
		// by pressing "C"/reset.
		m_out = e.what();
		m_firstDigitEntered = FALSE;
		m_errorInput = true;
	}
	// update output
	createHistoryText();
	if (operation == Calculator::ActionType::Equals)
	{
		if (m_errorInput)
			m_history += " ";
		m_history += m_out;
		m_result = m_out;
	}
	UpdateData(FALSE);
	m_firstDigitEntered = FALSE;
}