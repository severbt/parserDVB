#include "../include/descriptor.h"
#include "../include/DVB_types.h"
#include "../include/DVB_table.h"

void clear_list_desc(datad* p)
{
    if ( p == NULL)
    {
        return;
    }

    if ( p->_buf != NULL)
    {
        free(p->_buf);
    }

    datad* _next = NULL;
    datad* _tmp = p->_next;
    while(_tmp != NULL)
    {
        if (_tmp->_buf != NULL)
        {
            free(_tmp->_buf);
        }
        _next = _tmp->_next;
        free(_tmp);
        _tmp = _next;
    }
}

void clear_list_loop(tsloop* p)
{
    if ( p == NULL )
    {
        return;
    }

    tsloop* _next = NULL;
    tsloop* _tmp = p->_next;

    clear_list_desc(&p->_d1);

    while(_tmp != NULL)
    {
        clear_list_desc(&_tmp->_d1);
        _next = _tmp->_next;
        free(_tmp);
        _tmp = _next;
    }
}

//@param
//str - array data
//n   - length byte
//p   - &datad!!!
int parse_descriptor(unsigned char* str, const uint16_t n, datad* p)
{
    uint8_t _len = 0;
    datad*   next_p = p;

    if ( next_p == NULL || str == NULL )
    {
        return -1;
    }

    do
    {
        next_p->_tag.u = (*(uint8_t*)str);
        next_p->_len.u = (*(uint8_t*)str + 1);
        str += 2;
        _len += next_p->_len.u ;

        next_p->_buf = allocate_uc(next_p->_len);
        if ( next_p->_buf == NULL )
        {
            return -1;
        }

        memcpy(next_p->_buf, str, next_p->_len.u);
        str += next_p->_len.u;

        if (_len < n)
        {
            datad* tmp = (datad*)malloc(sizeof(datad));
            if ( tmp == NULL)
            {
                clear_list_desc(p);
                return -1;
            }
            next_p->_next = tmp;
            next_p = next_p->_next;
        }
        else
        {
            break;
        }
    }while(1);

    return 1;
}

int parse_trans_loop(unsigned char* str, const uint16_t n, tsloop* p)
{
    int32_t len_all = 0;
    int32_t len_parse = 0;
    tsloop* p_next = p;
    if (str == NULL || p_next == NULL)
    {
        return (-1);
    }

    do
    {
        p_next->_tra_id.u  = (*(uint16_t*)str + len_all);
        p_next->_net_id.u  = (*(uint16_t*)str + len_all + 2);
        p_next->_tra_len.u = (*(uint16_t*)str + len_all + 4) & MASK_SECTION_NET_LEN;
        len_all += 6;

        len_parse = parse_descriptor(str + len_all, p_next->_tra_len.u, &p_next->_d1);
        if ( len_parse < 1)
        {
            clear_list_loop(p);
            len_all = -1;
            break;
        }
        else if( len_parse > 0 )
        {
            len_all += len_parse;
        }

        if ( len_all < n)
        {
            p_next->_next = (tsloop*)malloc(sizeof(tsloop));
            if (p_next->_next == NULL)
            {
                clear_list_loop(p);
                len_all = -1;
                break;
            }
            p_next = p_next->_next;
        }
        else
        {
            break;
        }

    }while(1);

    return (len_all);
}
