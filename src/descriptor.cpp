#include <stddef.h>

#include "../include/descriptor.h"
#include "../include/DVB_types.h"

using namespace std;

void tableDesc( const _u8_t val );
void network_name_desc(const string& str);
void service_list_desc(const string& str);

int DVB::parseTransportStream(const string& str)
{
    _u16_t idtrans = 0;
    _u16_t idorigin = 0;
    _u16_t translen = 0;

    _u16_t i = 0;
    const _u16_t lmax = str.length();

    do
    {
        idtrans = (((_u8_t)str[i]) << 8) | (_u8_t)str[i+1];
        idorigin = (((_u8_t)str[i+2]) << 8) | (_u8_t)str[i+3];
        translen = (((_u8_t)str[i+4] & 0x0F) << 8) | (_u8_t)str[i+5];

        i += 6;
        if ( translen > lmax)
        {
            break;
        } else if ( translen > 0)
        {
            printf( "  transport stream id : %d\n"
                    "  original network id : %d\n"
                    "  transport descriptor len : %d\n", idtrans, idorigin,  translen);

            parseDescriptor(str.substr(i, translen));
            i += translen;
        }
    }while( i < lmax);
}

int DVB::parseDescriptor(const string& str)
{
    int result = -1;

    _u8_t tag     = 0;
    _u16_t size_d = 0;
    _u16_t size_str = str.length();

    _u16_t i = 0;
    do
    {
        tag    = (_u8_t)str[i];
        size_d = (_u8_t)str[i + 1];

        i += 2;
        if (size_d > size_str)
        {
            break;
        }
        else if (size_d > 0)
        {
            printf("  tad descriptor    : %x\n"
                   "  length descriptor : %u\n",tag, size_d);

            switch(tag)
            {
                case 0x40:
                {
                    network_name_desc(str.substr(i, size_d));
                    break;
                }
                case 0x41:
                {
                    service_list_desc(str.substr(i, size_d));
                    break;
                }
                default:
                {
                    break;
                }
            }

            i += size_d;
        }

    }while( i < size_str );

    return result;

}

void network_name_desc(const string& str)
{
    _u16_t len = str.length();

    printf("        Network name : ");

    for(size_t i = 0; i < len; ++i)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

void service_list_desc(const string& str)
{
    _u16_t service_id   = 0;
    _u8_t  service_type = 0;

    _u16_t len = str.size();
    _u16_t i   = 0;

    while( i < len)
    {
        service_id   = ((_u8_t)str[i] << 8) | (_u8_t)str[i+1];
        service_type =  (_u8_t)str[i+2];

        i += 3;

        printf("    |service id   :%x"
               "    |service type :%x\n", service_id, service_type);
    }
    /*_u16_t new_orig_id  = 0;
    _u16_t new_trans_id = 0;
    _u16_t new_serv_id  = 0;

    if (str.length() == 6)
    {
        new_orig_id  = ((_u8_t)str[0] << 8) | (_u8_t)str[1];
        new_trans_id = ((_u8_t)str[2] << 8) | (_u8_t)str[3];
        new_serv_id  = ((_u8_t)str[4] << 8) | (_u8_t)str[5];

        printf("    |new original network id :%d"
               "    |new transport stream id :%d"
               "    |new service id          :%d\n\n", new_orig_id, new_trans_id, new_serv_id);

    }*/
}


