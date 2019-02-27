#include "table_descriptors.h"

typedef struct nit_section
{
    __u8   _tid;
    __u8   _sindi; //section indicator
    __u8   _resf0; //reserved future use
    __u8   _res0;  //reserved
    __u16  _slen;  //section length
    __u16  _nid;   //network id
    __u8   _res1;  //reserved
    __u8   _vern;  //version number
    __u8   _cnext; //current next indicator
    __u8   _secn;  //section number
    __u8   _lsecn; //last section number
    __u8   _resf1; //reserved future use

    __u16  _ndlen; //network descriptor length
    nndesc _dn;
    _byte* _pn;

    __u8  _resf2; //reserved future use
    __u16 _tstrlen; //transport stream loop length
    tsloop* _tl;

    __u32 _CRC_32;

    nit_section* _next;
    nit_section* _prev;

} nit_section;

typedef struct nit_table
{
    nit_section* root;

} nit_table
