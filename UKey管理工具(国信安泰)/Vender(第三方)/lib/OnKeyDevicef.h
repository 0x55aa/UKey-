
ONKEY_FUNCTION_INFO(SKF_EnumDev)
#ifdef ONKEY_NEED_ARG_LIST
(
 OUT LPSTR pszReaders,
 IN  DWORD dwMaxLen
);
#endif

ONKEY_FUNCTION_INFO(OnKey_DeviceExists)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  LPCSTR pszReader
);
#endif

ONKEY_FUNCTION_INFO(SKF_ConnectDev)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  LPCSTR pszReader,
 IN  DWORD dwMode,
 OUT PS_DEV_HANDLE phDev
);
#endif

ONKEY_FUNCTION_INFO(SKF_Transmit)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  BYTE* pbCommand,
 IN  DWORD ulCommandLen,
 OUT BYTE* pbData,
 OUT DWORD* pulDataLen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_LoadConfig)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwFlags
);
#endif


ONKEY_FUNCTION_INFO(SKF_DisConnectDev)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwMode
);
#endif


ONKEY_FUNCTION_INFO(SKF_GetDeviceInfo)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 OUT LPBYTE pDevInfo
);
#endif


ONKEY_FUNCTION_INFO(OnKey_InitDevice)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN PS_DEV_HANDLE phDev,
 IN	PS_DEV_INITINFO pInit
);
#endif


ONKEY_FUNCTION_INFO(SKF_GenRandom)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 OUT LPBYTE pbRand,
 IN  DWORD dwRandLen
);
#endif


ONKEY_FUNCTION_INFO(SKF_SetLabel)//SKF_SetLabel (DEVHANDLE hDev, LPSTR szLabel);
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  LPBYTE pbData,
 IN  DWORD dwDataLen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_ReadBin)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwFileID,
 IN  DWORD dwOffset,
 IN  DWORD dwDataLen,
 OUT LPBYTE pbData
);
#endif


ONKEY_FUNCTION_INFO(OnKey_UpdateBin)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwFileID,
 IN  DWORD dwOffset,
 IN  DWORD dwDataLen,
 IN  LPBYTE pbData
);
#endif



ONKEY_FUNCTION_INFO(SKF_VerifyPIN)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwPinType,
 IN  LPBYTE pbPin,
 IN  DWORD  dwPinLen
 );
#endif


ONKEY_FUNCTION_INFO(SKF_ChangePin)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwPinType,
 IN  LPBYTE pbOldPin,
 IN  DWORD  dwOldPinLen,
 IN  LPBYTE pbNewPin,
 IN  DWORD  dwNewPinLen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_ReloadPin)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwPinType,
 IN  LPBYTE pbSoPin,
 IN  DWORD  dwSoPinLen,
 IN  LPBYTE pbUserPin,
 IN  DWORD  dwUserPinLen
);
#endif

ONKEY_FUNCTION_INFO(OnKey_GeneratePairKey)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwModBits,
 IN  LPBYTE pbE,
 IN  DWORD dwELen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_ImportPairKey)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwKeyFlag,
 IN  LPBYTE pbKeyStr,
 IN  DWORD dwKeyLen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_ExportPairKey)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwKeyFlag,
 OUT LPBYTE pbKeyStr,
 IN OUT LPDWORD pdwKeyLen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_RsaEncrypt)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  LPBYTE pbData,
 IN  DWORD dwDataLen,
 OUT LPBYTE pbEncryptedData,
 IN OUT  LPDWORD pdwEncryptedDataLen
);
#endif


ONKEY_FUNCTION_INFO(OnKey_RsaDecrypt)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  LPBYTE pbEncryptedData,
 IN  DWORD pdwEncryptedDataLen,
 OUT LPBYTE pbData,
 IN OUT  LPDWORD dwDataLen
);
#endif


ONKEY_FUNCTION_INFO(SKF_RSASignData)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwHashFlags,
 IN  LPBYTE pbData,
 IN  DWORD dwDataLen,
 OUT LPBYTE pbSignature,
 IN OUT LPDWORD pdwSignatureLen
);
#endif

ONKEY_FUNCTION_INFO(OnKey_RsaVerify)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwHashFlags,
 IN  LPBYTE pbSignature,
 IN  DWORD pdwSignatureLen,
 OUT LPBYTE pbData,
 IN OUT  LPDWORD dwDataLen
);
#endif

ONKEY_FUNCTION_INFO(OnKey_DevAlgCalc)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  BYTE bEncrypt,
 IN  DWORD dwMode, //ecb or cbc
 IN  LPBYTE pbKey,
 IN  LPBYTE pbIn,
 IN  DWORD dwInLen,
 OUT  LPBYTE pbOut,
 OUT  DWORD *pdwOutLen
);

#endif
ONKEY_FUNCTION_INFO(OnKey_EccSign)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwHashFlags,
 IN  LPBYTE pbData,
 IN  DWORD dwDataLen,
 OUT LPBYTE pbSignature,
 IN OUT LPDWORD pdwSignatureLen
 );
#endif
ONKEY_FUNCTION_INFO(OnKey_EccVerify)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  DWORD dwHashFlags,
 IN  LPBYTE pbSignature,
 IN  DWORD dwSignatureLen,
 OUT LPBYTE pbData,
 IN OUT LPDWORD pdwDataLen
 );
#endif
ONKEY_FUNCTION_INFO(OnKey_EccDecrypt)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  LPBYTE pbEncryptedData,
 IN  DWORD dwEncryptedDataLen,
 OUT LPBYTE pbData,
 IN OUT LPDWORD pdwDataLen
 );
#endif
ONKEY_FUNCTION_INFO(OnKey_EccEncrypt)
#ifdef ONKEY_NEED_ARG_LIST
(
 IN  PS_DEV_HANDLE phDev,
 IN  DWORD dwKeyIndex,
 IN  LPBYTE pbData,
 IN  DWORD dwDataLen,
 OUT LPBYTE pbEncryptedData,
 IN OUT  LPDWORD pdwEncryptedDataLen
 );
#endif
