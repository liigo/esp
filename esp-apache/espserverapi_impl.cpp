#include "espserverapi_impl.h"


//use free() to free the returned data
static char* ReadPostedRequestData(request_rec* r, size_t& rdatalen)
{
	rdatalen = 0;
	size_t rdataalloclen = 1024;
	char* rdata = (char*) malloc(rdataalloclen);

	apr_bucket* bucket;
	apr_bucket_brigade* bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
	if(bb == NULL) return NULL;

	int seen_eos = 0;

    do {
        apr_status_t rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                                         APR_BLOCK_READ, HUGE_STRING_LEN);
        if (rv != APR_SUCCESS) {
			if(rdata) free(rdata);
            return NULL;
        }

        for(bucket = APR_BRIGADE_FIRST(bb); bucket != APR_BRIGADE_SENTINEL(bb); bucket = APR_BUCKET_NEXT(bucket))
        {
            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }

            /* We can't do much with this. */
            if (APR_BUCKET_IS_FLUSH(bucket)) {
                continue;
            }

            /* read */
            const char *data;
            apr_size_t len;
            apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);

			/* append to rdata */
			if(rdataalloclen - rdatalen < len)
			{
				rdataalloclen *= 2;
				rdata = (char*) realloc(rdata, rdataalloclen);
			}
			memcpy(rdata + rdatalen, data, len);
			rdatalen += len;
        }
        apr_brigade_cleanup(bb);
    }
    while (!seen_eos);

	apr_brigade_destroy(bb);

	if(rdatalen == 0)
	{
		free(rdata); return NULL;
	}
	else
	{
		if(rdataalloclen == rdatalen)
			rdata = (char*) realloc(rdata, rdataalloclen + 1);
		rdata[rdatalen] = '\0'; //在数据结尾处添加'\0'以便于后续处理,该结尾符不算在rdatalen中
		return rdata;
	}

}
