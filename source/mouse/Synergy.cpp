#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int MouseClickTest()
{
	INPUT_RECORD Inrec; //���콺�� Ű���� �̺�Ʈ�� ������ ����ü
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
				//FROM_LEFT_1ST_BUTTON_PRESSED �̰�1
				//FROM_LEFT_2ND_BUTTON_PRESSED �̰�2
				if(FROM_LEFT_1ST_BUTTON_PRESSED & Inrec.Event.MouseEvent.dwButtonState) //����Ŭ�� �Է�ó��
					{
						nClickNum |= 0x01;
					}
				if(FROM_LEFT_2ND_BUTTON_PRESSED & Inrec.Event.MouseEvent.dwButtonState) // �� Ŭ�� �Է�ó��
					{
						nClickNum |= 0x04;
					}
				if(RIGHTMOST_BUTTON_PRESSED & Inrec.Event.MouseEvent.dwButtonState) // ������ Ŭ�� �Է�ó��
					{
						nClickNum |= 0x02;
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
	return nClickNum;
}


int _tmain(int argc, TCHAR* argv[])
{
	POINT p;
	DWORD px,py;
	DWORD temp;
	_tprintf(_T("%d\n"), GetSystemMetrics(SM_CYVIRTUALSCREEN));
	_tprintf(_T("%d\n"),GetSystemMetrics(SM_CYSCREEN));
	// GetSystemMetrics(SM_CXSCREEN) �Լ��� ���� �ָ������ �ʺ� �����Ѵ�
	// GetSystemMetrics(SM_CYSCREEN) �Լ��� ���� �ָ������ ���̸� �����Ѵ�
	// GetSystemMetrics(SM_CYVIRTUALSCREEN) ���������� ���̸� �����Ѵ�
	// GetSystemMetrics(SM_CXVIRTUALSCREEN) �γʸ������ �ʺ��� ���� �����Ѵ�
	// GetSystemMetrics(SM_CMONITORS) ����� ����� ������ �����´�. ��������ȵǸ�0 ������ϳ���1 �����̸�2

/*
	while(2!=MouseClickTest()) //��Ŭ�����ϸ� Ż��
	{
		_tprintf(_T("right click!\n"));
		Sleep(25);
	}*/
	while(1){ // ��Ŭ���ϸ� Ż��
		GetCursorPos(&p);	//���콺 ��ġ��������
		//printf("%d, %d \n", p.x, p.y); //���콺��ġ���
		px=p.x;
		py=p.y;
		temp = MouseClickTest();
		if(1==temp)
			_tprintf(_T("click!\n"));
		else if(2==temp)
			_tprintf(_T("right click!\n"));
		else if(3==temp)
			break;
		else if(4==temp)
			_tprintf(_T("wheel click!\n"));

		if(px==(GetSystemMetrics(SM_CXVIRTUALSCREEN)-1))
			SetCursorPos(1,py); //���콺 ��ġ�� �̵���Ű��
		
		if(px==0)
			SetCursorPos(GetSystemMetrics(SM_CXVIRTUALSCREEN)-2,py); //���콺 ��ġ�� �̵���Ű��

		//���콺 ���� -> �Ʒ���, �Ʒ��� -> ����
		if(GetSystemMetrics(SM_CXVIRTUALSCREEN)-GetSystemMetrics(SM_CXSCREEN) > px){
			if(py==(GetSystemMetrics(SM_CYSCREEN)-1))
				SetCursorPos(px,1); //���콺 ��ġ�� �̵���Ű��
			if(py==0)
				SetCursorPos(px,GetSystemMetrics(SM_CYSCREEN)-2); //���콺 ��ġ�� �̵���Ű��
		}else{
			if(py==(GetSystemMetrics(SM_CYVIRTUALSCREEN)-1))
				SetCursorPos(px,1); //���콺 ��ġ�� �̵���Ű��
			if(py==0)
				SetCursorPos(px,GetSystemMetrics(SM_CYVIRTUALSCREEN)-2); //���콺 ��ġ�� �̵���Ű��
		}

	}
	return 0;
}