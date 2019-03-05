#pragma once

#include "../include/DVB_types.h"

namespace DVB
{
    class DVB_parse_stream
    {
    public:

        DVB_parse_stream(){};
        DVB_parse_stream( const _u32_t size_buf);

        void        init(const _u32_t size_buf);

        void       addStream(const std::string& str);
        void       addStream(const _byte* str, const _u32_t size_buf);
        void       addStream(const _byte* start_str, const _byte* end_str);

        const int  getPack(ts_pack& o_pack);
    private:

        const size_t findStartPack();
        void         parsePack(head_pack& hs);
        const bool   checkPack(const head_pack& hs, ts_pack& o_pack);
        void         clearRest();


    private:
        std::string m_stream;
        std::string m_reststream;
    };
}



