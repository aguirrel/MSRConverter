// ImageLoader.cpp: implementation of the CImageLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSRConverter.h"
#include "ImageLoader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageLoader::CImageLoader()
{
}

CImageLoader::~CImageLoader()
{

}

bool CImageLoader::GetFiles(std::vector<CString>& a_fileList, CString a_sExtension)
{
    bool btmpOk;

    try
    {
        a_fileList.clear();
        WIN32_FIND_DATA tmpFileFindData;

        // Found for Path\*.Extension
        CString stmpFiles = m_sPath + CString("*.") + a_sExtension;

        HANDLE tmpHdFind = FindFirstFile(stmpFiles, &tmpFileFindData);
        bool btmpFi = (tmpHdFind == INVALID_HANDLE_VALUE);
        while (!btmpFi)
        {
            // If we found a file and it is not a directory, we put it into the vector.
            CString stmpFileName = tmpFileFindData.cFileName;
            if (!((tmpFileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY))
                a_fileList.push_back(m_sPath + stmpFileName);
            btmpFi = (FindNextFile(tmpHdFind, &tmpFileFindData) == 0);
        }
        btmpOk = true;
    }
    catch(...)
    {
        btmpOk = false;
    }

    return btmpOk;
}

bool CImageLoader::SetBitmap(CStatic* a_Static, int a_iIndex /* = -1 */)
{
    bool btmpOk;

    try
    {
        CString stmpBMP = GetBmpName(a_iIndex);

        HANDLE tmphBMP1 = LoadImage(NULL, stmpBMP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
        HANDLE tmphBMP2 = a_Static->SetBitmap((HBITMAP)tmphBMP1);
        if (tmphBMP2 != NULL)
            DeleteObject(tmphBMP2), tmphBMP2 = NULL;
        a_Static->CenterWindow();
    }
    catch(...)
    {
        btmpOk = false;
    }

    return btmpOk;
}

void CImageLoader::NewCursor(int a_iIndex /* = -1 */)
{
    CString stmpICO = GetIcoName(a_iIndex);

    HANDLE tmphICO = LoadImage(NULL, stmpICO, IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    if (tmphICO != NULL)
    {
        DestroyCursor(GetCursor());
        SetCursor((HICON)tmphICO);
    }
}


CString CImageLoader::GetBmpName(int a_iIndex /* = -1 */)
{
    CString stmpRes = "";
    if (m_BmpNameList.size() > 0)
    {
        int itmpIndex = a_iIndex;
        if ((itmpIndex < 0)||(itmpIndex >= m_BmpNameList.size()))
            itmpIndex = rand()%(m_BmpNameList.size());
        stmpRes = m_BmpNameList[itmpIndex];
    }

    return stmpRes;
}

CString CImageLoader::GetIcoName(int a_iIndex /* = -1 */)
{
    CString stmpRes = "";
    if (m_IcoNameList.size() > 0)
    {
        int itmpIndex = a_iIndex;
        if ((itmpIndex < 0)||(itmpIndex >= m_IcoNameList.size()))
            itmpIndex = rand()%(m_IcoNameList.size());
        stmpRes = m_IcoNameList[itmpIndex];
    }

    return stmpRes;
}


int CImageLoader::GetBmpListSize()
{
    return m_BmpNameList.size();
}


int CImageLoader::GetIcoListSize()
{
    return m_IcoNameList.size();
}

// ACCESSORS
void CImageLoader::SetPath(CString a_sPath)
{ 
    m_sPath = a_sPath;
    if (m_sPath[m_sPath.GetLength()-1] != '\\')
        m_sPath += "\\";

    GetFiles(m_BmpNameList, "bmp");
    GetFiles(m_IcoNameList, "ico");
}

CString CImageLoader::GetPath() 
{ 
    return m_sPath; 
}
