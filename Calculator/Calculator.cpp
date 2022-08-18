
// Calculator.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorApp

BEGIN_MESSAGE_MAP(CCalculatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCalculatorApp construction

CCalculatorApp::CCalculatorApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCalculatorApp object

CCalculatorApp theApp;


// CCalculatorApp initialization

BOOL CCalculatorApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager* pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CCalculatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


#include "Calculator.h"

Calculator::Action Calculator::getLastInput() const
{
	return m_actions.size() <= 0 ? Action{ ActionType::None, 0.0 } : m_actions.back();
}

void Calculator::reset()
{
	m_leftExpression.reset();
	m_leftTerm.reset();
	m_actions.clear();
}

bool Calculator::isOperation(ActionType action) const
{
	return (action == ActionType::Plus || action == ActionType::Minus ||
		action == ActionType::Multiply || action == ActionType::Divide ||
		action == ActionType::Equals);
}

bool Calculator::isTerm(ActionType action) const
{
	return (action == ActionType::Multiply || action == ActionType::Divide);
}

bool Calculator::isExpression(ActionType action) const
{
	return (action == ActionType::Plus || action == ActionType::Minus);
}

Calculator::ActionType Calculator::getLastOperation()
{
	for (auto op = m_actions.rbegin(); op != m_actions.rend(); ++op)
	{
		if (isOperation(op->actionType))
			return op->actionType;
	}
	return ActionType::None;
}

double Calculator::getCurrentResult() const
{
	// If "+" or "-" has been entered then this function always returns the current 
	// m_leftExpression value.
	// After "=" m_leftExpression contains the current result. If after "=" a term
	// is pressed (and no expression is pressed) then m_leftExpression is reset and
	// m_leftTerm contains the current result.
	return m_leftExpression.hasValue() ? m_leftExpression.getValue() : m_leftTerm.getValue();
}

void Calculator::deleteLastAction(Action temp)
{
	if (getLastInput().actionType != ActionType::Number)
		m_actions.pop_back();
	else
	{
		m_actions.pop_back();
		addInput(temp);
	}
}

// Logic: 
// - If it is a number then just add it to the actions vector (but adding two
// times a number is not allowed as "3 4 6 =" is not a correct syntax. "3 + 6 =" would be correct.)
// - If it is an expression-operation (like "3+4-") then do the operation with the operation before that
// ("3+4" in the example) and add it to "left expression" (m_leftExpression).
// - If it is a term-operation (like 3+4x) add the left number (3) to m_leftExpression and
// the right handside number (4) of the expression operation to m_leftTerm.
// - "=" and "None" as an operation means that a totally new calculation started from there,
// meaning that the first number after them are just assigned to "left expression" (m_leftExpression).
// After "=" and "None" the first temporary results (untill the next expression operator)
// go to m_leftTerm and m_leftExpression remains zero.
// return value: Returns true if input was valid otherwise false
bool Calculator::addInput(const Action& input)
{
	const Calculator::Action lastInput = getLastInput();

	if (input.actionType == ActionType::Number)
	{
		// adding a number after a number would be an error -> that entry is ignored
		if (lastInput.actionType != ActionType::Number)
			m_actions.push_back(input);
	}
	else if (isOperation(input.actionType))
	{
		if (lastInput.actionType == ActionType::Number)
		{
			ActionType lastOperation = getLastOperation();
			switch (lastOperation)
			{
			case ActionType::Plus:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					// "3 + 4 -", "3 + 4 ="
					m_leftExpression.add(lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					// "3 + 4 x",
					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Minus:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					// "3 - 4 -", "3 - 4 ="
					m_leftExpression.add(-lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					// "3 - 4 x",
					m_leftTerm.set(-lastInput.value);
				}
				break;
			case ActionType::Multiply:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					// "3 x 4 +", "3 x 4 ="
					m_leftExpression.add(m_leftTerm.getValue() * lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType)) // "3 x 4 x"
					m_leftTerm.multiplyBy(lastInput.value);
				break;
			case ActionType::Divide:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equals)
				{
					if (lastInput.value == 0.0)
					{
						CalculatorException divByZeroException("Error: Cannot Divide By Zero",
							CalculatorException::ExceptionType::DividedByZero);
						throw divByZeroException;
					}
					else
					{
						// "3 / 4 +", "3 / 4 ="
						m_leftExpression.add(m_leftTerm.getValue() / lastInput.value);
						m_leftTerm.reset();
					}
				}
				else if (isTerm(input.actionType)) // "3 / 4 x"
					m_leftTerm.multiplyBy(1.0 / lastInput.value);
				break;
			case ActionType::Equals: // "=" is the start of a new beginnning, see (h: *)
				if (isTerm(input.actionType))
				{
					// "= 3 x "
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value);
				}
				else if (isExpression(input.actionType))
				{
					// "= 3 + "
					m_leftExpression.set(lastInput.value);
					m_leftTerm.reset();
				}
				else
				{
					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::None: // "None" is the start of a new beginnning, see (h: *)
				if (isTerm(input.actionType))
				{
					// "3 x "
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value);
				}
				else if (isExpression(input.actionType))
				{
					// "3 + "
					m_leftExpression.set(lastInput.value);
					m_leftTerm.reset();
				}
				else if (input.actionType == ActionType::Equals)
				{
					m_leftTerm.set(lastInput.value);
				}
				break;
			}
			m_actions.push_back(input);
			return true;
		}
	}
	return false;
}

