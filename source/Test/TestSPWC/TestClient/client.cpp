#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <tchar.h>

void ErrorHandling(char* message);
LONG mousePosition[3];
int nClickNum;

void MouseControl()
{
	POINT p;
	//mousePosition = (LONG*) &param;
	p.x = mousePosition[0];
	p.y = mousePosition[1];
	SetCursorPos(p.x,p.y); //마우스 위치를 이동시키기
	/*마우스 왼쪽 -> 오른쪽, 오른쪽 -> 왼쪽*/
	if(p.x==(GetSystemMetrics(SM_CXVIRTUALSCREEN)-1))
			SetCursorPos(1,p.y); //마우스 위치를 이동시키기
	if(p.x==0)
			SetCursorPos(GetSystemMetrics(SM_CXVIRTUALSCREEN)-2,p.y); //마우스 위치를 이동시키기
	/*마우스 위쪽 -> 아래쪽, 아래쪽 -> 위쪽*/
	if(GetSystemMetrics(SM_CXVIRTUALSCREEN)-GetSystemMetrics(SM_CXSCREEN) > p.x){
			if(p.y==(GetSystemMetrics(SM_CYSCREEN)-1))
				SetCursorPos(p.x,1); //마우스 위치를 이동시키기
			if(p.y==0)
				SetCursorPos(p.x,GetSystemMetrics(SM_CYSCREEN)-2); //마우스 위치를 이동시키기
		}else{
			if(p.y==(GetSystemMetrics(SM_CYVIRTUALSCREEN)-1))
				SetCursorPos(p.x,1); //마우스 위치를 이동시키기
			if(p.y==0)
				SetCursorPos(p.x,GetSystemMetrics(SM_CYVIRTUALSCREEN)-2); //마우스 위치를 이동시키기
	}
	
}


void function()
{
	int nClickNum = mousePosition[2];	
	//if(nClickNum== 1 || nClickNum== 2 || nClickNum== 4 || nClickNum== 8)
	//{
	
	switch (nClickNum)
		{
			case 1:
			{	
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
				printf("마우스 왼쪽 클릭\n");
				break; 
			}
			case 4:
			{
				mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);
				printf("휠클릭\n");
				break;
			}
			case 2:
			{
				mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
				printf("마우스 오른쪽 클릭\n");
				break;
			}
			case 9:
			{
				printf("윈쪽 더블 클릭\n");
				break;
			}

			case 10:
			{
				printf("오른쪽 더블 클릭\n");
				break;

			}
		}
		

	//}
	
	  //gotoxy(0, 0);
	  //printf("%d,%d",nClickNum&0x01,  nClickNum&0x02);
		//printf("nClickNum : %d\n",nClickNum);
	
}

unsigned int WINAPI clientThread(LPVOID hSocket)
{
	int strLen;

	while(1){
		strLen = recv((SOCKET)hSocket, (char*)mousePosition, sizeof(mousePosition), 0);
		if(strLen == -1){
			ErrorHandling("read() error!");
			break;
		}
		function();
		MouseControl();
	}
	closesocket((SOCKET)hSocket);
	WSACleanup();	
	return 0;
	
}


int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	
	DWORD dwThreadId;
	HANDLE hThread;
	//POINT pon;
	
	if(argc!=3)
	{
		printf("Usage : %s <IP>\n", argv[0]);
		exit(1);
	}
	
	if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)	//소켓 라이브러리를 초기화
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);	//소켓 생성
	if(hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	servAddr.sin_port = htons(atoi(argv[2]));

	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR) //생성된 소켓을 바탕으로 서버에 연결 요청
		ErrorHandling("connect() error");
	
		
	hThread= (HANDLE)_beginthreadex(NULL, 0, clientThread, (LPVOID)hSocket,0,(unsigned *) &dwThreadId);
	
	while(1){
	}

	
	//소켓 라이브러리를 해제
	CloseHandle(hThread);
	//CloseHandle(hThread[1]);
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

