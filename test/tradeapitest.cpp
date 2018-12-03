/*// tradeapitest.cpp :
// һ���򵥵����ӣ�����CThostFtdcTraderApi��CThostFtdcTraderSpi�ӿڵ�ʹ�á�
// ��������ʾһ������¼������Ĺ���
#include <stdio.h>
#include <windows.h>
#include "FtdcTraderApi.h"
// ����¼������Ƿ���ɵı�־
// Create a manual reset event with no signal
HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);
// ��Ա����
TThostFtdcBrokerIDType g_chBrokerID;
// �����û�����
TThostFtdcUserIDType g_chUserID;
class CSimpleHandler : public CThostFtdcTraderSpi
{
public:
// ���캯������Ҫһ����Ч��ָ��CThostFtdcMduserApiʵ����ָ��
CSimpleHandler(CThostFtdcTraderApi *pUserApi) : m_pUserApi(pUserApi) {}
~CSimpleHandler() {}
// ���ͻ����뽻���й�ϵͳ������ͨ�����ӣ��ͻ�����Ҫ���е�¼
virtual void OnFrontConnected()
{
CThostFtdcReqUserLoginField reqUserLogin;
// get BrokerID
printf("BrokerID:");
scanf("%s", &g_chBrokerID);
strcpy(reqUserLogin. BrokerID, g_chBrokerID);
// get userid
printf("userid:");
scanf("%s", &g_chUserID);
strcpy(reqUserLogin.UserID, g_chUserID);
// get password
printf("password:");
scanf("%s", &reqUserLogin.Password);
// ������½����
m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
}
// ���ͻ����뽻���й�ϵͳͨ�����ӶϿ�ʱ���÷���������
virtual void OnFrontDisconnected(int nReason)
{
// ��������������API���Զ��������ӣ��ͻ��˿ɲ�������
printf("OnFrontDisconnected.\n");
}
// ���ͻ��˷�����¼����֮�󣬸÷����ᱻ���ã�֪ͨ�ͻ��˵�¼�Ƿ�ɹ�
virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
printf("OnRspUserLogin:\n");
printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID,
pRspInfo->ErrorMsg);
printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
if (pRspInfo->ErrorID != 0) {
// �˵�ʧ�ܣ��ͻ�������д�����
printf("Failed to login, errorcode=%d errormsg=%s requestid=%d
chain=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
exit(-1);
}
// �˵ǳɹ�,��������¼������
CThostFtdcInputOrderField ord;
memset(&ord, 0, sizeof(ord));
//���͹�˾����
strcpy(ord.BrokerID, g_chBrokerID);
//Ͷ���ߴ���
strcpy(ord.InvestorID, "12345");
// ��Լ����
strcpy(ord.InstrumentID, "cn0601");
///��������
strcpy(ord.OrderRef, "000000000001");
// �û�����
strcpy(ord.UserID, g_chUserID);
// �����۸�����
ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
// ��������
ord.Direction = THOST_FTDC_D_Buy;
// ��Ͽ�ƽ��־
strcpy(ord.CombOffsetFlag, "0");
// ���Ͷ���ױ���־
strcpy(ord.CombHedgeFlag, "1");
// �۸�
ord.LimitPrice = 50000;
// ����
ord.VolumeTotalOriginal = 10;
// ��Ч������
ord.TimeCondition = THOST_FTDC_TC_GFD;
// GTD����
strcpy(ord.GTDDate, "");
// �ɽ�������
ord.VolumeCondition = THOST_FTDC_VC_AV;
// ��С�ɽ���
ord.MinVolume = 0;
// ��������
ord.ContingentCondition = THOST_FTDC_CC_Immediately;
// ֹ���
ord.StopPrice = 0;
// ǿƽԭ��
ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
// �Զ������־
ord.IsAutoSuspend = 0;
m_pUserApi->ReqOrderInsert(&ord, 1);
}
// ����¼��Ӧ��
virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
// �������¼����
printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID,
pRspInfo->ErrorMsg);
// ֪ͨ����¼�����
SetEvent(g_hEvent);
};
///�����ر�
virtual void OnRtnOrder(CThostFtdcOrderField *pOrder)
{
printf("OnRtnOrder:\n");
printf("OrderSysID=[%s]\n", pOrder->OrderSysID);
}
// ����û�����ĳ���֪ͨ
virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
bool bIsLast) {
printf("OnRspError:\n");
printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID,
pRspInfo->ErrorMsg);
printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
// �ͻ�������д�����
{�ͻ��˵Ĵ�����}
}
private:
// ָ��CThostFtdcMduserApiʵ����ָ��
CThostFtdcTraderApi *m_pUserApi;
};
int main()
{
// ����һ��CThostFtdcTraderApiʵ��
CThostFtdcTraderApi *pUserApi =
CThostFtdcTraderApi::CreateFtdcTraderApi();
// ����һ���¼������ʵ��
CSimpleHandler sh(pUserApi);
// ע��һ�¼������ʵ��
pUserApi->RegisterSpi(&sh);
// ����˽����
// TERT_RESTART:�ӱ������տ�ʼ�ش�
// TERT_RESUME:���ϴ��յ�������
// TERT_QUICK:ֻ���͵�¼��˽����������
pUserApi->SubscribePrivateTopic(TERT_RESUME);
// ���Ĺ�����
// TERT_RESTART:�ӱ������տ�ʼ�ش�
// TERT_RESUME:���ϴ��յ�������
// TERT_QUICK:ֻ���͵�¼�󹫹���������
pUserApi->SubscribePublicTopic(TERT_RESUME);
// ���ý����й�ϵͳ����ĵ�ַ������ע������ַ����
pUserApi->RegisterFront("tcp://172.16.0.31:57205");
// ʹ�ͻ��˿�ʼ���̨����������
pUserApi->Init();
// �ͻ��˵ȴ������������
WaitForSingleObject(g_hEvent, INFINITE);
// �ͷ�APIʵ��
pUserApi->Release();
return 0;
}*/