#include "compress.h"

CCompressTask::CCompressTask(const QString& src, const QString& dst, bool bzip)
    : m_sSrc(src)
    , m_sDst(dst)
    , m_bzip(bzip)
{}

CCompressTask::~CCompressTask()
{}

void CCompressTask::run()
{
    int ret;
    //TPSYS::TPSYS_COMPRESS_RESULT ret;
    //if (m_bzip){
    //    ret = TPSYS::tpsys_compress(m_sSrc, m_sDst);
    //}
    //else{
    //    ret = TPSYS::tpsys_uncompress(m_sSrc, m_sDst);
    //}
    m_sSrc = "thread_src";
    m_sDst = "thread_dst";
    ret = 99;
    m_bzip = false;
    emit sigTaskFinished(m_sSrc, m_sDst, (int)ret, m_bzip);
}