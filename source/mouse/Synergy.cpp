// Synergy.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include <stdio.h>
#include <windows.h>
#include <tchar.h>


int main(int argc, char **argv)
{
	POINT p;
	int px,py;
	printf("%d\n", GetSystemMetrics(SM_CYVIRTUALSCREEN));

	printf("%d\n",GetSystemMetrics(SM_CYSCREEN));
	// GetSystemMetrics(SM_CXSCREEN) �Լ��� ���� �ָ������ �ʺ� �����Ѵ�
	// GetSystemMetrics(SM_CYSCREEN) �Լ��� ���� �ָ������ ���̸� �����Ѵ�
	// GetSystemMetrics(SM_CYVIRTUALSCREEN) ���������� ���̸� �����Ѵ�
	// GetSystemMetrics(SM_CXVIRTUALSCREEN) �γʸ������ �ʺ��� ���� �����Ѵ�
	// GetSystemMetrics(SM_CMONITORS) ����� ����� ������ �����´�. ��������ȵǸ�0 ������ϳ���1 �����̸�2
	
	while(1){
		GetCursorPos(&p);	//���콺 ��ġ��������
		//printf("%d, %d \n", p.x, p.y); //���콺��ġ���
		px=p.x;
		py=p.y;

		/*���콺 ���� -> ������, ������ -> ����*/
		if(px==(GetSystemMetrics(SM_CXVIRTUALSCREEN)-1))
			SetCursorPos(1,py); //���콺 ��ġ�� �̵���Ű��
		if(px==0)
			SetCursorPos(GetSystemMetrics(SM_CXVIRTUALSCREEN)-2,py); //���콺 ��ġ�� �̵���Ű��

		/*���콺 ���� -> �Ʒ���, �Ʒ��� -> ����*/
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