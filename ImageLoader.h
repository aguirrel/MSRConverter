// ImageLoader.h: interface for the CImageLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGELOADER_H__35CD6E17_F248_4051_9476_83B3F8CD3FE9__INCLUDED_)
#define AFX_IMAGELOADER_H__35CD6E17_F248_4051_9476_83B3F8CD3FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CImageLoader  
{
  protected:
    /// Full path were the images and icons are stored
    CString m_sPath;
    /// List with all the Bmp found in m_sPath
    std::vector<CString> m_BmpNameList;
    /// List with all the ico found in m_sPath
    std::vector<CString> m_IcoNameList;

    /**
     * If fills the a_fileList with all the files with extension a_sExtension
     * found int the path m_sPath
     * @param a_fileList: std::vector<CString>& where the file names will be stored
     * @param a_sExtension: CString with the extension of the files to found
     * @return bool true if all ok
     */
    bool GetFiles(std::vector<CString>& a_fileList, CString a_sExtension);

  public:
	CImageLoader();
	~CImageLoader();

    /** 
     * Load a bitmap into the static
     * @param a_Static: CStatic* in which the bitmap will be loaded
     * @param a_iIndex: int with the index of bitmap to load. If it is -1
     *  then it will take one bmp randomly. Default value: -1
     * @return bool indicating if it load the bitmap correctly.
     */
    bool SetBitmap(CStatic* a_Static, int a_iIndex = -1);

    /**
     * Change the actual cursor for a new ico that is in the
     * @param a_iIndex: int position in the array. If it is -1 then it will take one
     * bmp randomly. Default value -1.
     */
    void NewCursor(int a_iIndex = -1);

    /**
     * It returns a name of a Bmp.
     * @param a_iIndex: int position of the BMP name to return in the array. 
     *  If it is -1 then it will return a name randomly. Default value -1.
     * @return CString with the BMP name
     */
    CString GetBmpName(int a_iIndex = -1);

    /**
     * It returns a name of a Ico.
     * @param a_iIndex: int position of the ICO name to return in the array. 
     *  If it is -1 then it will return a name randomly. Default value -1.
     * @return CString with the ICO name
     */
    CString GetIcoName(int a_iIndex = -1);

    /**
     * It return the number of BMP names stored in the attribute m_BmpNameListt
     * @return int with the lengtg of m_BmpNameList
     */
    int GetBmpListSize();

    /**
     * It return the number of BMP names stored in the attribute m_IcoNameList
     * @return int with the lengtg of m_IcoNameList
     */
    int GetIcoListSize();

    // Accesors
    /// Write Accesor for m_sPath attribute
    void SetPath(CString a_sPath);
    /// Read Accesor for m_sPath attribute
    CString GetPath();
};

#endif // !defined(AFX_IMAGELOADER_H__35CD6E17_F248_4051_9476_83B3F8CD3FE9__INCLUDED_)
