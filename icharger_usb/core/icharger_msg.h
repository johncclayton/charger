#ifndef _MEMSTRUCT
#define _MEMSTRUCT

#pragma pack(1)   

typedef unsigned long	u32;
typedef signed long	s32;
typedef unsigned short	u16;
typedef signed short	s16;
typedef unsigned char   u8;
typedef signed char     s8;

#define MODEL_MAX	2

typedef  struct _SYSTEM
{
	u16 TempUnit;	
	u16 TempStop;					
	u16 TempFansOn;					
	u16 TempReduce;					
	u16 FansSpeed;					
	u16 FansOffDelay;				 
	u16 LcdContraste;				
	u16 LightValue;					
	u16 BeepMode;					
	u16 BeepType[4];				
	u16 BeepEnable[4];				
	u16 BeepVOL[4];					
	u16 DoneBeepType;    
	u16 SelectAdj;
	u16 Ver;					       
	u16 SelInputSource;			     
	u16 DCInputLowVolt;			
	u16 DCInputOverVolt;			
	s16 DCInputCurrentLimit;		
	u16 BatInputLowVolt;		       
	u16 BatInputOverVolt;			
	s16 BatInputCurrentLimit;		
	u16 RegEnable;				
	u16 RegVoltLimit;			
	s16 RegCurrentLimit;			
	u16 ChargePower[MODEL_MAX];		
	u16 DischargePower[MODEL_MAX];	
	u16 ProPower;			
        u16 MonitorLogInterval[MODEL_MAX];		   
	u16 MonitorLogSaveToSD[MODEL_MAX]; 

	u16 ServoType;		      
	u16 ServoUserCenter;	
	u16 ServoUserRate;	
	u16 ServoUserOpAngle;	
	
	u16 ModBusMode;		
	u16 ModBusAddr;		

	u16 Dump[10];			    
} SYSTEM;

#define LIST_MEM_MAX		64
typedef struct _MEM_HEAD
{
	u16 Count;
	u8 Index[LIST_MEM_MAX];
}MEM_HEAD;

#define MEM_HEAD_DEFAULT	{7,{0,1,2,3,4,5,6}}

enum{
	BAL_START_CV,
	BAL_START_CV_100,
	BAL_START_CV_200,
	BAL_START_CV_300,
	BAL_START_CV_400,
	BAL_START_CV_500,
	BAL_START_CV_600,
	BAL_START_CV_700,
	BAL_START_CV_800,
	BAL_START_CV_900,
	BAL_START_CV_1000,
	BAL_START_ALWAY,
};

enum{
	BAL_SPEED_SLOW,
	BAL_SPEED_NORMAL,
	BAL_SPEED_FAST,
	BAL_SPEED_USER,
};

enum{
	LI_MODE_C_BAL,	
	LI_MODE_C_NOTBAL,
};

enum{
	NI_MODE_C_NORMAL,
	NI_MODE_C_REFLEX,
};

enum{
	PB_MODE_C_NORMAL,
	PB_MODE_C_REFLEX,
};

enum{
	CYCLE_MODE_C2D,
	CYCLE_MODE_D2C,
};

enum{
	REG_DCHG_OFF,
	REG_DCHG_INPUT,
	REG_DCHG_CH,
	REG_DCHG_AUTO,
};

#define MEM_NAME_LEN	37
typedef struct _MEMORY
{
	u16 UseFlag;					//ʹ�ñ���
	s8 Name[MEM_NAME_LEN+1];		//��������
	u32 Capacity;					//��������
	u8 AutoSave;					//���������Զ�����
	u8 LiBalEndMode;				//Li����ƽ����������ģʽ
	u8 LockFlag;					//������������
	u8 LockPWD[6];					//������������
	u16 OpEnable;					//ģ���Ƿ�ʹ��:��bit0-15λ�ֱ���ʾCharge(bit0) ,Storage(bit2) ,Discharge(bit3) ,Cycle(bit4) ,OnlyBalance(bit5) 

	u8 ChannelMode;					//CH1|CH2,CH1&CH2,CH1,CH2	
	u8 SaveToSD;					//=0:������log��SD =1:����log��SD
	u16 LogInterval;				//�������� 0.1S Ϊ1����λ
	u16 RunCounter;					//���д���ͳ�� 

	u8 Type;						//����: LiPo,LiLo,LiFe,NiMH,Nicd,Pb
	u8 LiCell;						//Li���ش���
	u8 NiCell;						//Ni���ش���
	u8 PbCell;						//Pb���ش���

	u8 LiModeC;						//����ģʽ: Normal,Balance
	u8 LiModeD;						//�ŵ�ģʽ: Normal,Balance,External
	u8 NiModeC;						//����ģʽ: Normal,REFLEX
	u8 NiModeD;						//�ŵ�ģʽ: 
	u8 PbModeC;						//����ģʽ: Normal,REFLEX
	u8 PbModeD;						//�ŵ�ģʽ: 

	u8 BalSpeed;					//ƽ���ٶ�: 0--slow 1--normal 2--fast
	u8 BalStartMode;				//ƽ����ʼģʽ: 0--���� 1--CV�׶� 2--ָ����ʼ��ѹ�� 
	u16 BalStartVolt;				//ƽ����ʼ��ѹ
	u8 BalDiff;						//ƽ��ֹͣ����(mV)
	u8 BalOverPoint;				//ƽ������ѹֵ
	u8 BalSetPoint;					//ƽ����������ʱ������ѹ��������ֵ.����: 4.2V��LiPo,BalSetPoint=5,�Ǿ�4.195V����ֹͣ
	u8 BalDelay;					//ƽ���Ƴٽ���ʱ��
	
	u8 KeepChargeEnable;			//����

	u16 LiPoChgCellVolt;			//LiPo���ص���������ѹ
	u16 LiLoChgCellVolt;			//LiLo���ص���������ѹ
	u16 LiFeChgCellVolt;			//LiFe���ص���������ѹ
	
	u16 LiPoStoCellVolt;			//LiPo���ص����洢��ѹ
	u16 LiLoStoCellVolt;			//LiLo���ص����洢��ѹ
	u16 LiFeStoCellVolt;			//LiFe���ص����洢��ѹ

	u16 LiPoDchgCellVolt;			//LiPo�ŵ絥����ֹ��ѹ
	u16 LiLoDchgCellVolt;			//LiLo�ŵ絥����ֹ��ѹ
	u16 LiFeDchgCellVolt;			//LiFe�ŵ絥����ֹ��ѹ

	u16 ChargeCurrent;				//���ó�������
	u16 DischargeCurrent;			//���÷ŵ�����

	u16 EndCharge;					//������������
	u16 EndDischarge;				//�ŵ���������
	u16 RegDchgMode;				//�ŵ�ģʽ: OFF(�ڲ��ŵ�),���յ������ŵ�,���յ�����ͨ��,�Զ�����

	u16 NiPeak;						// ���������е�ѹ
	u16 NiPeakDelay;				// deltaV�����ӳ�

	u16 NiTrickleEnable;			//������������
	u16 NiTrickleCurrent;			//������������
	u16 NiTrickleTime;				//��������ʱ��

	u16 NiZeroEnable;				//Ni����0��ѹ����(���ڷ��������ж�����)
	
	u16 NiDischargeVolt;			//Ni�ŵ���ѹ
	u16 PbChgCellVolt;				//Pb���ص���������ѹ
	u16 PbDchgCellVolt;				//Pb���ص����ŵ���ѹ
	u16 PbFloatEnable;				//Pb���ص��帡������
	u16 PbFloatCellVolt;			//Pb���ص��帡����ѹ

	u16 RestoreVolt;				//��ѹ�ָ���ѹ
	u16 RestoreTime;				//��ѹ�ָ�ʱ��
	u16 RestoreCurent;				//��ѹ�ָ�����
	//
	//ѭ������
	u16 CycleCount;					//ѭ������
	u16 CycleDelay;					//ѭ������ʱ��
	u8 CycleMode;					//ѭ��ģʽ
	
	//��ȫ����
	u16 SafetyTimeC;				//��ȫʱ��
	u16	SafetyCapC;					//��ȫ����%
	u16 SafetyTempC;				//��ȫ�¶�
	u16 SafetyTimeD;				//��ȫʱ��
	u16	SafetyCapD;					//��ȫ����%
	u16 SafetyTempD;				//��ȫ�¶�

//#ifdef REG_CH
	u8 RegChMode;					//ͨ������ģʽ
	u16 RegChVolt;					//ͨ���������Ƶ�ѹ
	u16 RegChCurrent;				//ͨ���������Ƶ���
//#endif

//#ifdef FAST_STO
	u8 FastSto;						//����﮵��ش洢	
	u16 StoCompensation;			//�洢������ѹ
//#endif

//#ifdef NIZN
	u16 NiZnChgCellVolt;			//NiZn���ص���������ѹ
	u16 NiZnDchgCellVolt;			//NiZn�ŵ絥����ֹ��ѹ
	u8 NiZnCell;					//NiZn���ش���
//#endif
	u8 Dump;		//����Ҫ,�����ṹ����ҪΪ˫��,�����洢���ܶ�ʧ����������

}MEMORY;

#define NI_ZERO_VOLT		500	   //NI����0��ѹ������׼

#define CAP_MIN				0
#define CAP_MAX				999900
#define CAP_STEP			100
#define CAP_DEFAULT			0

#define RUN_COUNT_MIN				0
#define RUN_COUNT_MAX				999
#define RUN_COUNT_STEP				1
#define RUN_COUNT_DEFAULT			0

#define LOG_INTERVAL_MIN				5
#define LOG_INTERVAL_MAX				600
#define LOG_INTERVAL_STEP				5
#define LOG_INTERVAL_DEFAULT			10

#define BT_TYPE_MIN				0
#define BT_TYPE_MAX				(BT_MAX-1)
#define BT_TYPE_STEP			1
#define BT_TYPE_DEFAULT			0

#define LI_CELLS_MIN	   0
#define LI_CELLS_MAX	   CELL_MAX
#define LI_CELLS_DEFAULT   0

#define NI_CELLS_MIN	   0
#define NI_CELLS_MAX	   HW_NI_CELLS_MAX
#define NI_CELLS_DEFAULT   0

#define PB_CELLS_MIN	   1
#define PB_CELLS_MAX	   HW_PB_CELLS_MAX
#define PB_CELLS_DEFAULT   6

#define RESTORE_VOLT_MIN		500  //��ѹ�ָ���ѹMIN
#define RESTORE_VOLT_MAX		2500  //��ѹ�ָ���ѹMAX
#define RESTORE_VOLT_DEFAULT	1000

#define RESTORE_TIME_MIN		1 //��ѹ�ָ�ʱ��MIN
#define RESTORE_TIME_MAX		5 //��ѹ�ָ�ʱ��MAX
#define RESTORE_TIME_DEFAULT	3

#define RESTORE_CURRENT_MIN		2  //��ѹ�ָ�����MIN
#define RESTORE_CURRENT_MAX		50	//��ѹ�ָ�����MAX
#define RESTORE_CURRENT_DEFAULT	10

//#ifdef NIZN
#define NIZN_CELLS_MIN		0
#define NIZN_CELLS_MAX		CELL_MAX
#define NIZN_CELLS_DEFAULT  0

#define NIZN_CHG_MIN		1200
#define NIZN_CHG_MAX		2000
#define NIZN_CHG_DEFAULT	1900

#define NIZN_DCHG_MIN		900
#define NIZN_DCHG_MAX		1600
#define NIZN_DCHG_DEFAULT	1100

#define NIZN_STD			1650
#define NIZN_MIN			RESTORE_VOLT_MIN
#define NIZN_MAX			(NIZN_CHG_MAX+50)
//#endif

//#define LITYPE_FE			2
#define LI_BAL_VOLT_MIN			3000
#define LI_BAL_VOLT_MAX			4200
#define LI_BAL_VOLT_DEFAULT		3500

#define LI_BAL_DIFF_MIN			1
#define LI_BAL_DIFF_MAX			10
#define LI_BAL_DIFF_DEFAULT		5

#define LI_BAL_SETPOINT_MIN			1
#define LI_BAL_SETPOINT_MAX			50
#define LI_BAL_SETPOINT_DEFAULT		5

#define LI_BAL_DELAY_MIN			0
#define LI_BAL_DELAY_MAX			20
#define LI_BAL_DELAY_DEFAULT		1

#define LI_BAL_OVER_MIN			0
#define LI_BAL_OVER_MAX			10
#define LI_BAL_OVER_DEFAULT		0

#define LIFE_CHG_MIN		3300
#define LIFE_CHG_MAX		3800
#define LIFE_CHG_DEFAULT	3600

#define LIFE_STO_MIN		3100
#define LIFE_STO_MAX		3400
#define LIFE_STO_DEFAULT	3300

#define LIFE_DCHG_MIN		2000
#define LIFE_DCHG_MAX		3500
#define LIFE_DCHG_DEFAULT	2500

#define LIFE_STD			3300
#define LIFE_MIN			RESTORE_VOLT_MIN
#define LIFE_MAX			(LIFE_CHG_MAX+50)

#define LIFE_ADJ_STEP		1

//#define LITYPE_LO			1
#define LIIO_CHG_MIN		3750
#define LIIO_CHG_MAX		4350
#define LIIO_CHG_DEFAULT	4100

#define LIIO_STO_MIN		3600
#define LIIO_STO_MAX		3800
#define LIIO_STO_DEFAULT	3750

#define LIIO_DCHG_MIN		2500
#define LIIO_DCHG_MAX		4000
#define LIIO_DCHG_DEFAULT	3500

#define LIIO_STD			3600
#define LIIO_MIN			RESTORE_VOLT_MIN
#define LIIO_MAX			(LIIO_CHG_MAX+50)

#define LIIO_ADJ_STEP		1

#define LIPO_CHG_MIN		3850
#define LIPO_CHG_MAX		4350
#define LIPO_CHG_DEFAULT	4200

#define LIPO_STO_MIN		3700
#define LIPO_STO_MAX		3900
#define LIPO_STO_DEFAULT	3850

#define LI_STO_COMP_MIN		0
#define LI_STO_COMP_MAX		200
#define LI_STO_COMP_DEFAULT	10

#define LIPO_DCHG_MIN		3000
#define LIPO_DCHG_MAX		4100
#define LIPO_DCHG_DEFAULT	3500

#define LIPO_STD			3700
#define LIPO_MIN			RESTORE_VOLT_MIN
#define LIPO_MAX			(LIPO_CHG_MAX+50)

#define LIPO_ADJ_STEP		1

#define NI_STD				1200

#define PB_STD				2000

#define PB_CHG_MIN			2000
#define PB_CHG_MAX			2600
#define PB_CHG_DEFAULT		2400

#define PB_FLOAT_MIN		2200
#define PB_FLOAT_MAX		2400
#define PB_FLOAT_DEFAULT	2300

#define PB_DCHG_MIN			1500
#define PB_DCHG_MAX			2400
#define PB_DCHG_DEFAULT		1800

#define PB_ADJ_STEP			1

#define MEM_EMPTY			0xffff
#define MEM_USED			0x55aa
#define MEM_FIXED			0x0000
#define MEM_SIZE			256

#define CYCLE_COUNT_MIN		1		//ѭ����MIN
#define CYCLE_COUNT_MAX		99 //ѭ����MAX
#define CYCLE_COUNT_DEFAULT	3

#define CYCLE_TIME_MIN		0		//ѭ������ʱ��MIN
#define CYCLE_TIME_MAX		9999 //ѭ������ʱ��MAX
#define CYCLE_TIME_DEFAULT	3

#define	SAFETY_TEMP_MIN		200	//��ȫ�¶�MIN
#define	SAFETY_TEMP_MAX		800 //��ȫ�¶�MAX
#define	SAFETY_TEMP_DEFAULT	450

#define	SAFETY_CAP_MIN		50	//��ȫ����MIN
#define	SAFETY_CAP_MAX		200 //��ȫ����MAX
#define	SAFETY_CAP_DEFAULT	120

#define	SAFETY_TIME_MIN		0	//��ȫʱ��MIN
#define	SAFETY_TIME_MAX		9999 //��ȫʱ��MAX
#define	SAFETY_TIME_DEFAULT	0

#define	END_CURRENT_C_MIN		1	//������������MIN
#define	END_CURRENT_C_MAX		50 	//������������MAX
#define	END_CURRENT_C_DEFAULT	10

#define	END_CURRENT_D_MIN		1	//�ŵ���������MIN
#define	END_CURRENT_D_MAX		100 //�ŵ���������MAX
#define	END_CURRENT_D_DEFAULT	50

#define END_CURRENT_STO_MAX	10		//�洢���������������ٷֱ�

#define	CURRENT_MIN			5	//���ŵ�����MIN
#define	CURRENT_MAX			(SET_CURRENT_MAX) //���ŵ�����MAX
#define	CURRENT_DEFAULT		200
#define CURRENT_SYN_MAX		SET_ALL_CURRENT_MAX //ͬ��ģʽ���ŵ�����MAX

#define	VOLT_D_MIN 				100
#define	VOLT_D_MAX 				40000
#define	VOLT_D_DEFAULT			10

#define NI_PEAK_SENS_MIN		1
#define NI_PEAK_SENS_MAX		20
#define NIMH_PEAK_SENS_DEFAULT	3
#define NICD_PEAK_SENS_DEFAULT	5

#define NI_PEAK_DELAY_MIN		0
#define NI_PEAK_DELAY_MAX		20
#define NI_PEAK_DELAY_DEFAULT	3

#define NI_TRICKLE_CURRENT_MIN			2
#define NI_TRICKLE_CURRENT_MAX			100
#define NI_TRICKLE_CURRENT_DEFAULT		5

#define NI_TRICKLE_TIME_MIN			1
#define NI_TRICKLE_TIME_MAX			999
#define NI_TRICKLE_TIME_DEFAULT		5

#define BAL_DIFF_SLOW			3
#define BAL_POINT_SLOW			3
#define BAL_OVER_SLOW			0
#define BAL_DELAY_SLOW			2

#define BAL_DIFF_NORMAL			LI_BAL_DIFF_DEFAULT
#define BAL_POINT_NORMAL		LI_BAL_SETPOINT_DEFAULT
#define BAL_OVER_NORMAL			LI_BAL_OVER_DEFAULT	
#define BAL_DELAY_NORMAL		LI_BAL_DELAY_DEFAULT	

#define BAL_DIFF_FAST			8
#define BAL_POINT_FAST			8
#define BAL_OVER_FAST			5
#define BAL_DELAY_FAST			0

enum
{
	REG_CH_TYPE_RES,
	REG_CH_TYPE_BAT,
};
#define REG_CH_VOLT_DEFAULT		12000
#define REG_CH_CURRENT_DEFAULT	100

#define MEMORY_DEFAULT {															\
	MEM_USED,						/*ʹ�ñ���*/									\
	{0},							/*��������*/									\
	CAP_DEFAULT,			/*��������*/									\
	0,								/*�Զ�����*/								\
	0,							/*Li����ƽ����������ģʽ*/								\
	0xff,							/*������������*/								\
	{0xff,0xff,0xff,0xff,0xff,0xff},			/*������������*/								\
	0xffff,							/*ģ���Ƿ�ʹ��*/								\
	0,								/*����ͨ��ѡ��*/								\
	1,								/*=0:������log��SD =1:����log��SD*/				\
	LOG_INTERVAL_DEFAULT,			/*��������0.1SΪ1����λ*/						\
	RUN_COUNT_DEFAULT,								/*���д���ͳ��*/								\
	BT_TYPE_DEFAULT,								/*����: LiPo,LiLo,LiFe,NiMH,Nicd,Pb*/			\
	LI_CELLS_DEFAULT,								/*Li���ش���*/									\
	NI_CELLS_DEFAULT,								/*Ni���ش���*/									\
	PB_CELLS_DEFAULT,								/*Pb���ش���*/									\
	LI_MODE_C_BAL,					/*Li����ģʽ:Not Balance,Balance*/			\
	0,								/*Li�ŵ�ģʽ: Normal,Balance,External*/						\
	NI_MODE_C_NORMAL,				/*Ni����ģʽ*/									\
	0,								/*Ni�ŵ�ģʽ*/									\
	0,								/*Pb����ģʽ*/									\
	0,								/*Pb�ŵ�ģʽ*/									\
	BAL_SPEED_NORMAL,		/*ƽ���ٶ�*/  \
	BAL_START_CV_200,							/*ƽ����ʼģʽ*/									\
	LI_BAL_VOLT_DEFAULT,			/*ƽ����ʼ��ѹ*/								\
	LI_BAL_DIFF_DEFAULT,			/*ƽ��ֹͣ����(mV)*/							\
	LI_BAL_OVER_DEFAULT,			/*ƽ��������(mV)*/							\
	LI_BAL_SETPOINT_DEFAULT,		/*ƽ����������ʱ������ѹ��������ֵ*/			\
	LI_BAL_DELAY_DEFAULT,			/*ƽ���Ƴٽ���ʱ��*/							\
	0,								/*����*/										\
	LIPO_CHG_DEFAULT,				/*LiPo���ص���������ѹ*/						\
	LIIO_CHG_DEFAULT,				/*LiLo���ص���������ѹ*/						\
	LIFE_CHG_DEFAULT,				/*LiFe���ص���������ѹ*/						\
	LIPO_STO_DEFAULT,				/*LiPo���ص����洢��ѹ*/						\
	LIIO_STO_DEFAULT,				/*LiLo���ص����洢��ѹ*/						\
	LIFE_STO_DEFAULT,				/*LiFe���ص����洢��ѹ*/						\
	LIPO_DCHG_DEFAULT,				/*LiPo�ŵ絥����ֹ��ѹ*/						\
	LIIO_DCHG_DEFAULT,				/*LiLo�ŵ絥����ֹ��ѹ*/						\
	LIFE_DCHG_DEFAULT,				/*LiFe�ŵ絥����ֹ��ѹ*/						\
	CURRENT_DEFAULT,				/*���ó�������*/								\
	CURRENT_DEFAULT,				/*���÷ŵ�����*/								\
	END_CURRENT_C_DEFAULT,			/*EndCharge������������*/						\
	END_CURRENT_D_DEFAULT,			/*EndDischarge�ŵ���������*/					\
	REG_DCHG_OFF,					/*RegDchgMode�ŵ�ģʽ*/							\
	NIMH_PEAK_SENS_DEFAULT,			/*���������е�ѹ*/								\
	NI_PEAK_DELAY_DEFAULT,			/*deltaV�����ӳ�*/								\
	0,								/*������������*/								\
	NI_TRICKLE_CURRENT_DEFAULT,		/*������������*/								\
	NI_TRICKLE_TIME_DEFAULT,		/*��������ʱ��*/								\
	0,								/*Ni����0��ѹ����(���ڷ��������ж�����)*/		\
	VOLT_D_DEFAULT,					/*NiMH�ŵ���ѹ*/								\
	PB_CHG_DEFAULT,					/*Pb���ص���������ѹ*/							\
	PB_DCHG_DEFAULT,				/*Pb���ص����ŵ���ѹ*/							\
	0,								/*Pb���ص��帡������*/							\
	PB_FLOAT_DEFAULT,				/*Pb���ص��帡����ѹ*/							\
	RESTORE_VOLT_DEFAULT,			/*��ѹ�ָ���ѹ*/								\
	RESTORE_TIME_DEFAULT,			/*��ѹ�ָ�ʱ��*/								\
	RESTORE_CURRENT_DEFAULT,		/*��ѹ�ָ�����*/								\
	CYCLE_COUNT_DEFAULT,			/*ѭ������*/									\
	CYCLE_TIME_DEFAULT,				/*ѭ������ʱ��*/								\
	CYCLE_MODE_C2D,					/*ѭ��ģʽ*/									\
	SAFETY_TIME_DEFAULT,			/*��ȫʱ��*/									\
	SAFETY_CAP_DEFAULT,				/*��ȫ����*/									\
	SAFETY_TEMP_DEFAULT,			/*��ȫ�¶�*/									\
	SAFETY_TIME_DEFAULT,			/*��ȫʱ��*/									\
	SAFETY_CAP_DEFAULT,				/*��ȫ����*/									\
	SAFETY_TEMP_DEFAULT,			/*��ȫ�¶�*/									\
	REG_CH_TYPE_RES,				/*ͨ������ģʽ*/								\
	REG_CH_VOLT_DEFAULT,			/*ͨ���������Ƶ�ѹ*/							\
	REG_CH_CURRENT_DEFAULT,			/*ͨ���������Ƶ���*/							\
	1,								/*����﮵��ش洢*/								\
	LI_STO_COMP_DEFAULT,			/*�洢������ѹ*/								\
	NIZN_CHG_DEFAULT,			/*NiZn���ص���������ѹ*/							\
	NIZN_DCHG_DEFAULT,			/*NiZn�ŵ絥����ֹ��ѹ*/							\
	NIZN_CELLS_DEFAULT,			/*NiZn���ش���*/									\
	0xff,										/*��˫����*/		\
}


#endif //MEMSTRUCT


