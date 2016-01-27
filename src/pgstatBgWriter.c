/**
 * pgstatBgWriter MIB group implementation
 *
 * Note: this file originally auto-generated by mib2c
 */

#include "pgstatmibd.h"
#include "pgstatBgWriter.h"

static oid pgstatBgWriter_oid[] = { 1, 3, 6, 1, 4, 1, 27645, 3, 20 };

struct variable1 pgstatBgWriter_vars[] = {
    {PGSTATBGWRITER_CHECKPOINTSTIMED, 		ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {1}},
    {PGSTATBGWRITER_CHECKPOINTSREQUESTED, 	ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {2}},
    {PGSTATBGWRITER_BUFFERSCHECKPOINT, 		ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {3}},
    {PGSTATBGWRITER_BUFFERSCLEAN, 			ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {4}},
    {PGSTATBGWRITER_MAXWRITTENCLEAN, 		ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {5}},
    {PGSTATBGWRITER_BUFFERSBACKEND, 		ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {6}},
    {PGSTATBGWRITER_BUFFERSALLOCATED, 		ASN_COUNTER, RONLY, getvalue_pgstatBgWriter, 1, {7}}
};

void
init_pgstatBgWriter(void)
{
    DEBUGMSGTL((PGSTATBGWRITER_NAME, "Initializing\n"));
    REGISTER_MIB(PGSTATBGWRITER_NAME, pgstatBgWriter_vars, variable1, pgstatBgWriter_oid);
}

static pgstatBgWriterData pgstatBgWriter_data;

/**
 * refresh numbers
 */
void
refresh_numbers_pgstatBgWriter(void) {
	time_t now;
	unsigned int diff;

	// use cache on these numbers to prevent going to database so frequently
	now = time (NULL);
	diff = (now - pgstatBgWriter_data.last_load);

	if (pgstatBgWriter_data.last_load == 0 || diff >= PGSTATBGWRITER_CACHE_TIMEOUT) {
		load_numbers_from_db_pgstatBgWriter();
		pgstatBgWriter_data.last_load = now;
	}
}

/**
 * load counters from database
 */
void
load_numbers_from_db_pgstatBgWriter(void) {
	PGresult *res;

    DEBUGMSGTL((PGSTATBGWRITER_NAME, "Loading numbers from DB\n"));

	res = PQexec(dbconn, "\
SELECT checkpoints_timed, checkpoints_req, \
	buffers_checkpoint, buffers_clean, \
	maxwritten_clean, buffers_backend, buffers_alloc \
FROM pg_stat_bgwriter");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		// TODO: improve exception handling
		fprintf(stderr, "SELECT command failed: %s", PQerrorMessage(dbconn));
		PQclear(res);
		//exit_nicely(conn);
	}

	pgstatBgWriter_data.checkpoints_timed = atoi(PQgetvalue(res, 0, 0));
	pgstatBgWriter_data.checkpoints_req = atoi(PQgetvalue(res, 0, 1));
	pgstatBgWriter_data.buffers_checkpoint = atoi(PQgetvalue(res, 0, 2));
	pgstatBgWriter_data.buffers_clean = atoi(PQgetvalue(res, 0, 3));
	pgstatBgWriter_data.maxwritten_clean = atoi(PQgetvalue(res, 0, 4));
	pgstatBgWriter_data.buffers_backend = atoi(PQgetvalue(res, 0, 5));
	pgstatBgWriter_data.buffers_alloc = atoi(PQgetvalue(res, 0, 6));

	PQclear(res);
}

u_char *
getvalue_pgstatBgWriter(struct variable *vp,
            oid * name,
            size_t * length,
            int exact, size_t * var_len, WriteMethod ** write_method)
{
    DEBUGMSGTL((PGSTATBGWRITER_NAME, "getvalue(%d)\n", vp->magic));

    if (header_generic(vp, name, length, exact, var_len, write_method) == MATCH_FAILED)
        return NULL;

	if (vp->magic >= PGSTATBGWRITER_FIRST && vp->magic <= PGSTATBGWRITER_LAST)
		refresh_numbers_pgstatBgWriter();

    switch (vp->magic) {
    case PGSTATBGWRITER_CHECKPOINTSTIMED:
        return (u_char *) & pgstatBgWriter_data.checkpoints_timed;
	case PGSTATBGWRITER_CHECKPOINTSREQUESTED:
        return (u_char *) & pgstatBgWriter_data.checkpoints_req;
	case PGSTATBGWRITER_BUFFERSCHECKPOINT:
        return (u_char *) & pgstatBgWriter_data.buffers_checkpoint;
	case PGSTATBGWRITER_BUFFERSCLEAN:
        return (u_char *) & pgstatBgWriter_data.buffers_clean;
	case PGSTATBGWRITER_MAXWRITTENCLEAN:
        return (u_char *) & pgstatBgWriter_data.maxwritten_clean;
	case PGSTATBGWRITER_BUFFERSBACKEND:
        return (u_char *) & pgstatBgWriter_data.buffers_backend;
	case PGSTATBGWRITER_BUFFERSALLOCATED:
        return (u_char *) & pgstatBgWriter_data.buffers_alloc;
    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in %s\n", vp->magic, PGSTATBGWRITER_NAME));
    }

    return NULL;
}

