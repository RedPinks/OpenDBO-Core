//***********************************************************************************
//
//	File		:	NtlPacket.h
//
//	Begin		:	2005-12-13
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	Network Packet Class
//
//***********************************************************************************

#pragma once

typedef unsigned long long      QWORD;


//------------------------------------------------------------------
//
//------------------------------------------------------------------
// 
typedef struct STHeaderBase
{
	WORD		wPacketLen:15;
	WORD		bEncrypt:1; // specify packet header encryption
	WORD		packetSequence;
	QWORD		checksumm;

} STHeaderBase, *LPSTHeaderBase;

#pragma pack(push, 1)  /* push current alignment to stack */
typedef struct PACKETDATA
{
	WORD	wOpCode;

} PACKETDATA, * LPPACKETDATA;
#pragma pack(pop)   /* restore original alignment from stack */


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const int		PACKET_LIMIT_SIZE = 0x7FFF; // except encrypt 1 bit
const int		PACKET_HEADSIZE	= sizeof(STHeaderBase);
const WORD		PACKET_MAX_SEQUENCE = 0xFFFF; // max value of packet sequence
const int		PACKET_MAX_SIZE = 4095; // �Ϲ������� ���Ǵ� packet �ִ� ��
//------------------------------------------------------------------



class CNtlPacket
{
public:


	CNtlPacket();
	CNtlPacket(CNtlPacket & rhs);
	CNtlPacket(BYTE * pPacketData, WORD wPacketBodySize);
	CNtlPacket(WORD wPacketBodySize);
	CNtlPacket(BYTE * pAttachBuffer);

	//
	//	CNtlPacket(BYTE * pBuffer, int nSize);

	//
	virtual ~CNtlPacket();


public:

	//
	void							Destroy();

	//
	void							AttachData(BYTE * pPacketBuffer, WORD wBufferUsedSize);

	//
	virtual void					Attach(BYTE * pPacketBuffer);
	//
	void							InitUseExternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize);
private:

	//
	void							Realloc(int nSize);



public:


	//
	bool							IsValidHeader();

	//
	bool							IsValidTailer();

	//
	bool							IsValidPacket();

	//
	void							CopyToBuffer(BYTE * pDestBuffer, int nSize);

	//
	void							CopyFromBuffer(BYTE * pSrcBuffer, int nSize);

	//
	void							ReadData(void * pDest, int nSize);

	//
	void							WriteData(void * pSrc, int nSize);

	virtual int						GetHeaderSize() {return PACKET_HEADSIZE;}

public:


	//
	void							SetPacket(BYTE * pPacketData, WORD wPacketSize);

	//
	virtual void					SetPacketLen(WORD wPacketLen);

	//
	void							SetUsedSize(WORD wSize) { m_wBufferUsedSize = wSize; }

	// ���� ���Ǵ� ���۱��̸� ���õǾ��ִ� �޽���ũ��� �����Ѵ�
	void							SetPacketLenToUsedSize() { m_wBufferUsedSize = GetPacketLen(); } 

	//
	void							AdjustPacketLen(WORD wPacketLen) { SetPacketLen(wPacketLen); SetPacketLenToUsedSize(); }



public:


	//
	BYTE *							GetPacketBuffer() { return m_pPacketBufferPtr; }

	//
	LPSTHeaderBase					GetPacketHeader() { return	m_pPacketHeader; }

	//
	BYTE *							GetPacketData() { return m_pPacketData; }

	//
	WORD							GetPacketLen() { return (WORD)GetHeaderSize() + GetPacketDataSize(); }

	//
	virtual WORD					GetPacketDataSize() { return m_pPacketHeader->wPacketLen; }

	//
	WORD							GetUsedSize() { return m_wBufferUsedSize; }


public:


	CNtlPacket &					operator =( CNtlPacket & rhs );

	CNtlPacket &					operator <<( CNtlPacket & rhs );

	CNtlPacket &					operator >>( CNtlPacket & rhs );


	CNtlPacket &					operator <<( bool arg );

	CNtlPacket &					operator <<( int arg );

	CNtlPacket &					operator <<( long arg );

	CNtlPacket &					operator <<( DWORD arg );

	CNtlPacket &					operator <<( LPTSTR arg );



	CNtlPacket &					operator >>( bool & arg );

	CNtlPacket &					operator >>( int & arg );

	CNtlPacket &					operator >>( long & arg );

	CNtlPacket &					operator >>( DWORD & arg );

	CNtlPacket &					operator >>( LPTSTR arg );


protected:

	void							Init();

	void							InitUseInternalBuffer(const BYTE * pPacketBuffer, WORD wBufferUsedSize);


protected:


	BYTE *							m_pAllocateBuffer;					// �޽��� ���� ������

	BYTE *							m_pPacketBufferPtr;					// �޽��� ���� ������

	BYTE *							m_pEndPos;							// �޽��� ������ �� ���� (���ٽ� �� ������ �Ѿ�� �ȵȴ�)

	WORD							m_wBufferUsedSize;					// �޽��� ������ ��� ũ��


	LPSTHeaderBase					m_pPacketHeader;					// ��Ŷ���
		
	BYTE *							m_pPacketData;						// ��Ŷ������

	BYTE *							m_pReadDataPos;						// �б� ����Ÿ ��ġ

	BYTE *							m_pWriteDataPos;					// ���� ����Ÿ ��ġ

};