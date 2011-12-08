#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h>



unsigned int WINAPI function(LPVOID p)
{
	INPUT_RECORD Inrec; //마우스나 키보드 이벤트를 저장한 구조체
	DWORD evRead;
	HANDLE hStdIn=NULL;
	DWORD dwMode;
	int  nClickNum=0;
	GetConsoleMode(hStdIn, &dwMode);
	 
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdIn, &dwMode);
	if(!(dwMode & ENABLE_MOUSE_INPUT))
	{
		if(TRUE != SetConsoleMode( hStdIn, dwMode | ENABLE_MOUSE_INPUT))
		{
			return 0;
		}
	}

	PeekConsoleInput(hStdIn, &Inrec, 1, &evRead);
  
	if( evRead>0) 
	{
		ReadConsoleInput(hStdIn, &Inrec, 1, &evRead);
		switch (Inrec.EventType )
		{
			case MOUSE_EVENT:
			{
				//FROM_LEFT_1ST_BUTTON_PRESSED 이건1
				//FROM_LEFT_2ND_BUTTON_PRESSED 이건2
				if(FROM_LEFT_1ST_BUTTON_PRESSED & Inrec.Event.MouseEvent.dwButtonState) //왼쪽클릭 입력처리
					{
						nClickNum |= 0x01;
						printf("마우스 왼쪽 클릭\n");
					}
				if(FROM_LEFT_2ND_BUTTON_PRESSED & Inrec.Event.MouseEvent.dwButtonState) // 휠 클릭 입력처리
					{
						nClickNum |= 0x04;
						printf("휠클릭\n");
					}
				if(RIGHTMOST_BUTTON_PRESSED & Inrec.Event.MouseEvent.dwButtonState) // 오른쪽 클릭 입력처리
					{
						nClickNum |= 0x02;
						printf("마우스 오른쪽 클릭\n");
					}
	
				break; 
			}
			case KEY_EVENT:
			{
				_tprintf(_T("No key\n"));
				break;
			}
		}
	}
	
  //gotoxy(0, 0);
  //printf("%d,%d",nClickNum&0x01,  nClickNum&0x02);
	//printf("nClickNum : %d\n",nClickNum);
	return nClickNum;
	
}



int _tmain(int argc, TCHAR* argv[])
{
	/*
	POINT p;
	DWORD threadhandle;
	HANDLE handle;
	
	handle = (HANDLE)_beginthreadex(NULL,0, function, (LPVOID) &p,0,(unsigned *) &threadhandle);
	printf("%d\n",GetLastError());
	printf("%d\n",threadhandle);
	Sleep(1000000000);
	if(handle == NULL)
	{
		printf("화면 출력 실패에요\n");
		exit(0);
	}
	
	CloseHandle(handle);
	*/
	POINT p;
	DWORD px,py;
	DWORD temp;
	DWORD threadhandle;
	_tprintf(_T("%d\n"), GetSystemMetrics(SM_CYVIRTUALSCREEN));
	_tprintf(_T("%d\n"),GetSystemMetrics(SM_CYSCREEN));
	 // 휠클릭하면 탈출
	while(1)
	{
	GetCursorPos(&p);	//마우스 위치값얻어오기
		//printf("%d, %d \n", p.x, p.y); //마우스위치출력
		px=p.x;
		py=p.y;
		temp =  (DWORD)_beginthreadex(NULL,0, function, (LPVOID) &p,0,(unsigned *) &threadhandle);
		if(px==(GetSystemMetrics(SM_CXVIRTUALSCREEN)-1))
			SetCursorPos(1,py); //마우스 위치를 이동시키기
		
		if(px==0)
			SetCursorPos(GetSystemMetrics(SM_CXVIRTUALSCREEN)-2,py); //마우스 위치를 이동시키기

		//마우스 위쪽 -> 아래쪽, 아래쪽 -> 위쪽
		if(GetSystemMetrics(SM_CXVIRTUALSCREEN)-GetSystemMetrics(SM_CXSCREEN) > px){
			if(py==(GetSystemMetrics(SM_CYSCREEN)-1))
				SetCursorPos(px,1); //마우스 위치를 이동시키기
			if(py==0)
				SetCursorPos(px,GetSystemMetrics(SM_CYSCREEN)-2); //마우스 위치를 이동시키기
		}else{
			if(py==(GetSystemMetrics(SM_CYVIRTUALSCREEN)-1))
				SetCursorPos(px,1); //마우스 위치를 이동시키기
			if(py==0)
				SetCursorPos(px,GetSystemMetrics(SM_CYVIRTUALSCREEN)-2); //마우스 위치를 이동시키기
		}
	}
	return 0;
}
/*
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);	//쓰레드 함수 정의

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID;
	long time;
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	//두번째 인자 TRUE : 수동모드(manual-reset mode)
	if(hEvent == NULL)
	{
		_fputts(_T("Event object creation error\n"), stdout);
		return -1;
	}

	hThread = (HANDLE)_beginthreadex(NULL,0,OutputThreadFunction, NULL, 0, (unsigned *) &dwThreadID);
	if(hThread ==0)
	{
		_fputts(_T("Thread creation error\n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string : "), stdout);
	_fgetts(string, 30, stdin);

	SetEvent(hEvent);	//event의 state를 signaled 상태로 전환


	time = GetCurrentTime();
	while(1)
	{
		if(time + 10 < GetCurrentTime())break;
	};//50mm 세컨드의 텀 주기

	WaitForSingleObject(hThread,INFINITE);

	CloseHandle(hEvent);
	CloseHandle(hThread);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	HANDLE handle = 00070892;


	return 0;
}

HWND WINAPI CreateWindow(win,"처음만드는 윈도우",WS_OVERLAPPEDWINDOW, 
	

void MouseClik(int Lbtn, int Rbtn) 
{ 
        switch(Lbtn) { 
        case 1:   

                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,NULL); 
                break; 
        case 2:   

                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,NULL); 
                break; 
        }  

        switch(Rbtn) { 
        case 1:   

                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,NULL); 
                break; 
        case 2:  
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,NULL); 
                break; 
        } 
}
*/