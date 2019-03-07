#include <stddef.h>

#include "../include/descriptor.h"
#include "../include/DVB_types.h"

using namespace std;

void tableDesc( const _u8_t val );
void network_name_desc(const string& str);
void service_list_desc(const string& str);
void satellite_delivery_sys_desc(const string& str);

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
                case 0x43:
                {
                    satellite_delivery_sys_desc(str.substr(i, size_d));
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

        printf("    |ID  %d  <%x>        Type %d  <%x>\n",service_id, service_id, service_type, service_type);
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

void satellite_delivery_sys_desc(const string& str)
{
    if ( str.size() != 11 )
    {
        printf("        Error - length != 11 bytes");
        return;

    }

    _u8_t  frequency[8]            = {};
    _u8_t  orbital_position[4]     = {};
    _u8_t  west_east_flag          = ((_u8_t)str[6] & 0x80) >> 7;
    _u8_t  polarization            = ((_u8_t)str[6] & 0x60) >> 5;
    _u8_t  roll_off                = ((_u8_t)str[6] & 0x18) >> 3;
    _u8_t  modulation_sys          = ((_u8_t)str[6] & 0x04) >> 2;
    _u8_t  modulation_typ          =  (_u8_t)str[6] & 0x03;
    _u8_t  symbol_rate[7]          = {};
    _u8_t  FEC_inner               =  (_u8_t)str[10] & 0x0F;

    for( _u8_t i = 0; i < 8; ++i)
    {
		frequency[i] = ((_u8_t)str[i/2] >> ((i%2 == 0)?(4):(0))) & 0x0F;
    }

	for( _u8_t i = 0; i < 4; ++i)
    {
        orbital_position[i] = ((_u8_t)str[4+i/2] >> ((i%2 == 0)?(4):(0))) & 0x0F;
    }

	for( _u8_t i = 0; i < 7; ++i)
    {
		symbol_rate[i] = ((_u8_t)str[7+i/2] >> ((i%2 == 0)?(0xF0 >> 4):(0))) & 0x0F;
    }

	printf("	|frequency        : %d%d%d,%d%d%d%d%d GHz\n", frequency[0]
												            , frequency[1]
												            , frequency[2]
												            , frequency[3]
												            , frequency[4]
												            , frequency[5]
												            , frequency[6]
												            , frequency[7]);

    printf("	|orbital position : %d%d%d,%d\n", orbital_position[0]
                                                , orbital_position[1]
                                                , orbital_position[2]
                                                , orbital_position[3]);

    printf("	|position         : ");
    if ( west_east_flag == 1 )
    {
        printf("eastern\n");
    }
    else
    {
        printf("western\n");
    }

    printf("	|polarization      : ");
    if ( polarization == 0x0 )
    {
        printf("linear - horizontal\n");
    }
    else if ( polarization == 0x1 )
    {
        printf("linear - vertical\n");
    }
    else if ( polarization == 0x2 )
    {
        printf("Circular - leaft\n");
    }
    else if ( polarization == 0x3 )
    {
        printf("Circular - right\n");
    }

    printf("	|modulation system  : ");
    if ( modulation_sys == 0x0)
    {
        printf("DVB-S\n");
    }
    else
    {
        printf("DVB-S2\n");
        printf("	|Roll-off           : ");
        if ( roll_off == 0x0 )
        {
            printf("0,35\n");
        }
        else if ( roll_off == 0x1 )
        {
            printf("0,25\n");
        }
        else if ( roll_off == 0x2 )
        {
            printf("0,20\n");
        }
        else if ( roll_off == 0x3 )
        {
            printf("reserved\n");
        }
    }

    printf("	|modulation type        : ");
    if ( modulation_typ  == 0x0 )
    {
        printf("Auto\n");
    }
    else if ( modulation_typ == 0x1 )
    {
        printf("QPSK\n");
    }
    else if ( modulation_typ == 0x2 )
    {
        printf("8PSK\n");
    }
    else if ( modulation_typ == 0x3 )
    {
        printf("16-QAM\n");
    }

    printf("	|Symbol rate : %d%d%d,%d%d%d%d Msymbol/s\n", symbol_rate[0]
                                                           , symbol_rate[1]
                                                           , symbol_rate[2]
                                                           , symbol_rate[3]
                                                           , symbol_rate[4]
                                                           , symbol_rate[5]
                                                           , symbol_rate[6]);

}

