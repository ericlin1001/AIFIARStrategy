#ifndef NEWNEU_ROBOT_SOCCER_09S_DEFINES_H_
#define NEWNEU_ROBOT_SOCCER_09S_DEFINES_H_

// Frequency
#define FREQUENCY				0.2f

/*
// whoseBall
#define ANYONES_BALL			0
#define BLUE_BALL				1//mine
#define YELLOW_BALL				2//opp

// DEGameGround
#define	LEFT_AREA				0
#define	RIGHT_AREA 				1

// DEStartState
#define	DEFENSE					1
#define	ATTACK					0

// DEStartMode
#define NORMAL					0
#define FREE_BALL				1
#define PENALTY_KICK			2
#define FREE_KICK				3
#define GOAL_KICK				4
#define UNDER_WAY				5

*/
// SimuroSot5 

#define PITCH_LENGTH 			220
#define PITCH_WIDTH 	 		180
#define PENALTY_AREA_LENGTH		35
#define PENALTY_AREA_WIDTH		80
#define GOAL_AREA_LENGTH		15
#define GOAL_AREA_WIDTH			50
#define GOAL_WIDTH				40
#define GOAL_DEPTH				15

#define ROBOT_LENGTH			4
#define BALL_SIZE				2.0

#define MAX_SPEED				100//rad/s

#endif  // NEWNEU_ROBOT_SOCCER_09S_DEFINES_H_

/*
1)	��������ԭ���ڳ���Χǽ�����½ǣ�����ͼ��X������ˮƽ���ң�Y������ˮƽ���ϣ�
2)	���ȵ�λΪ���ף�����Ϊ1��1��ȡֵ��Χȡ���ڳ��صĴ�С��
3)	�Ƕ�������㷽��ΪX��������ʱ��Ϊ����
4)	�Ƕȵ�λΪ����������Ϊ1��1��ȡֵ��ΧΪ(-180,180]��
*/
/*
0����������˵��������٣�ȡֵ��ΧΪ[-100,100]����λ��rad/s��
e)	public double home0_velocityRight��0����������˵��������٣�ȡֵ��ΧΪ[-100,100]����λ��rad/s��
*/
/*6)	��
ֱ��42.7mm����46g��
*/
/*2)	StrategyStep����
Cԭ�ͣ�extern "C" __declspec(dllexport) void StrategyStep ( Environment *env )
���ܣ�ʵ�ֿ��ƾ��ߣ����ݴ����״̬���ݾ��߳��������٣�����״̬�����е���Ӧ������ʵ����������˵Ŀ��ơ�
�������ڣ�30ms
*/
/*10)	����������������е��ٶȷ�Χ��[��100��100]����λ��rad/s��
���ֵİ뾶��2cm�������˷�Χ���ܻᵼ����������˷�����
�����߸��������ٳ���100ʱ������ƽֻ̨��100�㡣*/
/*������
     ������Ϊ7.5cm��7.5cm��4.5cm ��С�������ˡ�
*/
/*(a�����سߴ�
����Ϊ��ɫ�����γ��أ���ߴ���220cm��180cm ������5cm �ߣ�2.5cm ��İ�ɫΧǽ���ڳ��ص��Ľǹ̶��ĸ�7cm��7cm �ĵ����������Ա����������䡣
��b�����ر��(��¼2)
��Ȧ�뾶��25cm ����Ϊ������һ���ֵ�Բ���������߳�25cm ����ֱ��������5cm����Ҫֱ��/Բ�������ߡ������߽��ߺ���Ȧ����Ϊ��ɫ��3mm ������ʱ�����˵�վλ��Բ�����Ϊ��ɫ��
��c������
���ſ�40cm��û�к���������
��d������������
������ǡ��λ������ǰ��40cm ��ֱ�ߡ���������¼2 �е�����A�� ����λ������ǰ�ߴ�Ϊ50cm��15cm �ĳ���������
��e��������
����������¼2 �е�����B������ǰ�ߴ�Ϊ80cm��35cm �ĳ��������򣬻�������ƽ���������߳���Ϊ25cm ����ֱ�������߸߶�Ϊ5cm��
��f����
�ýۻ�ɫ�ĸ߶���������������ֱ��42.7mm����46g��
��g��������
     ������Ϊ7.5cm��7.5cm��4.5cm ��С�������ˡ�
*/