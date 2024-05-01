#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

short HowManyQuestions()
{
	short
		QuizQuestions = 1;
	do
	{
		cout << "How many Questions you want to answer: ";
		cin >> QuizQuestions;

	} while (QuizQuestions < 1);

	return QuizQuestions;
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

enum enQuestionLevel
{
	Easy = 1, Med = 2, Hard = 3, Mix = 4
};

enum enOperationType
{
	Add = 1, Sub = 2, Mul = 3, Div = 4, MixOpType = 5
};

enum enQuizzFinalResult
{
	Fail = 1, Pass = 2
};

struct strQuestionInfo
{
	short QuestionNumber = 0;
	int Num1 = 0;
	int Num2 = 0;
	enOperationType OperationType;
	string OperationSymbol = "";
	int QuestionAnswer = 0;
	int UserAnswer = 0;
};

struct strQuizz
{
	enQuizzFinalResult QuizzFinalResult;
	short NumberOfQuestions = 0;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	string QuestionLevelName = "";
	string OperationName = "";
};

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 1;
	do
	{
		cout << "Enter Questions Level [1] Easy [2] Med [3] Hard [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 1;
	do
	{
		cout << "Enter Operation Type [1] Add [2] Sub [3] Mul [4] Div [5] Mix ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int GetNumber(enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		return RandomNumber(1, 10);
		break;
	case enQuestionLevel::Med:
		return RandomNumber(10, 50);
		break;
	case enQuestionLevel::Hard:
		return RandomNumber(50, 100);
		break;
	case enQuestionLevel::Mix:
		return RandomNumber(1, 100);
		break;
	}
}

enOperationType GetRandomOperation()
{
	return (enOperationType)RandomNumber(1, 4);
}

string GetOperationSymbol(enOperationType OperationType)
{
	string OpertionTypes[4] = { "+", "-", "x", "/" };

	return OpertionTypes[OperationType - 1];
}

string GetQuestionName(enQuestionLevel QLevel)
{
	string QuestionsLevel[4] = { "Easy", "Med", "Hard", "Mix" };
	return QuestionsLevel[QLevel - 1];
}

string GetOperationName(enOperationType Operation)
{
	string Operations[5] = { "Add", "Sub", "Mul", "Div", "Mix" };
	return Operations[Operation - 1];
}

int Calculate(strQuestionInfo& QuestionInfo, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return QuestionInfo.Num1 + QuestionInfo.Num2;
		break;
	case enOperationType::Sub:
		return QuestionInfo.Num1 - QuestionInfo.Num2;
		break;
	case enOperationType::Mul:
		return QuestionInfo.Num1 * QuestionInfo.Num2;
		break;
	case enOperationType::Div:
		return QuestionInfo.Num1 / QuestionInfo.Num2;
		break;
	}
}

int GetQuestionAnswer(strQuestionInfo& QuestionInfo)
{
	enOperationType RandomOperation = GetRandomOperation();

	if (QuestionInfo.OperationType == enOperationType::MixOpType)
	{
		QuestionInfo.OperationType = RandomOperation;

		return Calculate(QuestionInfo, RandomOperation);

	}
	return Calculate(QuestionInfo, QuestionInfo.OperationType);
}

void PrintQuestionInfo(short QuestionsNumber, strQuestionInfo QuestionInfo)
{
	cout << "\nQuestion [" << QuestionInfo.QuestionNumber << "/" << QuestionsNumber << "] \n\n";
	cout << QuestionInfo.Num1 << endl;
	cout << QuestionInfo.Num2 << " ";
	cout << QuestionInfo.OperationSymbol << endl;
	cout << "__________" << endl;

}

void PrintQuestionResult(strQuestionInfo QuestionInfo)
{
	if (QuestionInfo.UserAnswer == QuestionInfo.QuestionAnswer)
	{
		system("color 2F");
		cout << "Right answer :-)\n\n";
	}
	else
	{
		system("color 4F");
		cout << "Wrong answer" << endl;
		cout << "The right answer is: " << QuestionInfo.QuestionAnswer << "\n\n";
	}
}

int ReadUserAnswer()
{
	int Number = 0;
	cin >> Number;
	return Number;
}

bool CheckUserAnswer(int RightAnswer, int UserAnswer)
{
	return UserAnswer == RightAnswer;
}

void PrintQuizzResult(strQuizz QuizzInfo)
{
	cout << "\n\n------------------------------------------\n\n";
	if (QuizzInfo.QuizzFinalResult == enQuizzFinalResult::Pass)
	{
		system("color 2F");
		cout << "Final Results is PASS :-)";
	}

	else
	{
		system("color 4F");
		cout << "Final Results is Fail:-(";
	}

	cout << "\n\n------------------------------------------\n\n";
}

void PrintFinalResults(strQuizz QuizzInfo)
{
	PrintQuizzResult(QuizzInfo);

	cout << "Number Of Questions    : " << QuizzInfo.NumberOfQuestions << endl;
	cout << "Number Of Right Answers: " << QuizzInfo.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << QuizzInfo.NumberOfWrongAnswers << endl;
	cout << "Question Level         : " << QuizzInfo.QuestionLevelName << endl;
	cout << "Operation Type         : " << QuizzInfo.OperationName << endl << endl;

}

strQuizz FillQuizzInfo(short NoOfQuestions, short NoOfRightAnswers, short NoOfWrongAnswers, enQuestionLevel QLevel, enOperationType OpType)
{
	strQuizz FinalResult;

	FinalResult.NumberOfQuestions = NoOfQuestions;
	FinalResult.NumberOfRightAnswers = NoOfRightAnswers;
	FinalResult.NumberOfWrongAnswers = NoOfWrongAnswers;
	FinalResult.OperationName = GetOperationName(OpType);
	FinalResult.QuestionLevelName = GetQuestionName(QLevel);

	if (NoOfRightAnswers >= NoOfWrongAnswers)
		FinalResult.QuizzFinalResult = enQuizzFinalResult::Pass;
	else FinalResult.QuizzFinalResult = enQuizzFinalResult::Fail;

	return FinalResult;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

strQuizz PalyGame(short HowManyQuestions)
{
	enQuestionLevel QuestionLevel = ReadQuestionLevel();
	enOperationType OperationType = ReadOperationType();

	strQuestionInfo QuestionInfo;
	short NumberOfQuestions = HowManyQuestions, NumberOfRigthAnswers = 0, NumberOfWrongAnswers = 0;

	for (short QuestionNumber = 1; QuestionNumber <= HowManyQuestions; QuestionNumber++)
	{
		QuestionInfo.QuestionNumber = QuestionNumber;
		QuestionInfo.OperationType = OperationType;
		QuestionInfo.Num1 = GetNumber(QuestionLevel);
		QuestionInfo.Num2 = GetNumber(QuestionLevel);
		QuestionInfo.QuestionAnswer = GetQuestionAnswer(QuestionInfo);
		QuestionInfo.OperationSymbol = GetOperationSymbol(QuestionInfo.OperationType);

		PrintQuestionInfo(HowManyQuestions, QuestionInfo);

		QuestionInfo.UserAnswer = ReadUserAnswer();

		PrintQuestionResult(QuestionInfo);

		if (QuestionInfo.UserAnswer == QuestionInfo.QuestionAnswer)
			NumberOfRigthAnswers++;
		else
			NumberOfWrongAnswers++;
	}

	return FillQuizzInfo(NumberOfQuestions, NumberOfRigthAnswers, NumberOfWrongAnswers, QuestionLevel, OperationType);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		strQuizz FinalResult = PalyGame(HowManyQuestions());
		PrintFinalResults(FinalResult);

		cout << "Do you want to play again ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

