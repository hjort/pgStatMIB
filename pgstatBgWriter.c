/*
 * Note: this file originally auto-generated by mib2c
 */

#include "pgstatmibd.h"
#include "pgstatBgWriter.h"

/** Initializes the pgstatBgWriter module */
void
init_pgstatBgWriter(void)
{
    const oid pgstatBgWriterCheckpointsTimed_oid[] = { 1,3,6,1,4,1,27645,3,10,1 };
    const oid pgstatBgWriterCheckpointsRequested_oid[] = { 1,3,6,1,4,1,27645,3,10,2 };
    const oid pgstatBgWriterBuffersCheckpoint_oid[] = { 1,3,6,1,4,1,27645,3,10,3 };
    const oid pgstatBgWriterBuffersClean_oid[] = { 1,3,6,1,4,1,27645,3,10,4 };
    const oid pgstatBgWriterMaxWrittenClean_oid[] = { 1,3,6,1,4,1,27645,3,10,5 };
    const oid pgstatBgWriterBuffersBackend_oid[] = { 1,3,6,1,4,1,27645,3,10,6 };
    const oid pgstatBgWriterBuffersAllocated_oid[] = { 1,3,6,1,4,1,27645,3,10,7 };

  DEBUGMSGTL(("pgstatBgWriter", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterCheckpointsTimed", handle_pgstatBgWriterCheckpointsTimed,
                               pgstatBgWriterCheckpointsTimed_oid, OID_LENGTH(pgstatBgWriterCheckpointsTimed_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterCheckpointsRequested", handle_pgstatBgWriterCheckpointsRequested,
                               pgstatBgWriterCheckpointsRequested_oid, OID_LENGTH(pgstatBgWriterCheckpointsRequested_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterBuffersCheckpoint", handle_pgstatBgWriterBuffersCheckpoint,
                               pgstatBgWriterBuffersCheckpoint_oid, OID_LENGTH(pgstatBgWriterBuffersCheckpoint_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterBuffersClean", handle_pgstatBgWriterBuffersClean,
                               pgstatBgWriterBuffersClean_oid, OID_LENGTH(pgstatBgWriterBuffersClean_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterMaxWrittenClean", handle_pgstatBgWriterMaxWrittenClean,
                               pgstatBgWriterMaxWrittenClean_oid, OID_LENGTH(pgstatBgWriterMaxWrittenClean_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterBuffersBackend", handle_pgstatBgWriterBuffersBackend,
                               pgstatBgWriterBuffersBackend_oid, OID_LENGTH(pgstatBgWriterBuffersBackend_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("pgstatBgWriterBuffersAllocated", handle_pgstatBgWriterBuffersAllocated,
                               pgstatBgWriterBuffersAllocated_oid, OID_LENGTH(pgstatBgWriterBuffersAllocated_oid),
                               HANDLER_CAN_RONLY
        ));
}

// TODO: put it all on a struct (pgstatBgWriterCache ?)
static u_long checkpoints_timed = 0;
static u_long checkpoints_req = 0;
static u_long buffers_checkpoint = 0;
static u_long buffers_clean = 0;
static u_long maxwritten_clean = 0;
static u_long buffers_backend = 0;
static u_long buffers_alloc = 0;

int rnd(int ceil) {
	return rand() % ceil + 1;
}

/**
 * refresh numbers
 */
void refreshNumbers() {

	// TODO: cache these numbers to prevent going to database so frequently
	// ...

	loadNumbersFromDB();
}

/**
 * load from database
 */
void loadNumbersFromDB(void) {
	PGresult *res;

	res = PQexec(dbconn, "\
SELECT checkpoints_timed, checkpoints_req, \
	buffers_checkpoint, buffers_clean, \
	maxwritten_clean, buffers_backend, buffers_alloc \
FROM pg_stat_bgwriter");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SELECT command failed: %s", PQerrorMessage(dbconn));
		PQclear(res);
		//exit_nicely(conn);
	}

	checkpoints_timed = atoi(PQgetvalue(res, 0, 0));
	checkpoints_req = atoi(PQgetvalue(res, 0, 1));
	buffers_checkpoint = atoi(PQgetvalue(res, 0, 2));
	buffers_clean = atoi(PQgetvalue(res, 0, 3));
	maxwritten_clean = atoi(PQgetvalue(res, 0, 4));
	buffers_backend = atoi(PQgetvalue(res, 0, 5));
	buffers_alloc = atoi(PQgetvalue(res, 0, 6));

	PQclear(res);
}

int
handle_pgstatBgWriterCheckpointsTimed(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & checkpoints_timed,
                                     /* the length of the data in bytes */
					sizeof(checkpoints_timed));
            //checkpoints_timed += rnd(3);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterCheckpointsTimed\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_pgstatBgWriterCheckpointsRequested(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & checkpoints_req,
                                     /* the length of the data in bytes */
					sizeof(checkpoints_req));
            //checkpoints_req += rnd(1);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterCheckpointsRequested\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_pgstatBgWriterBuffersCheckpoint(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & buffers_checkpoint,
                                     /* the length of the data in bytes */
					sizeof(buffers_checkpoint));
            //buffers_checkpoint += rnd(256);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterBuffersCheckpoint\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_pgstatBgWriterBuffersClean(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & buffers_clean,
                                     /* the length of the data in bytes */
					sizeof(buffers_clean));
            //buffers_clean += rnd(2);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterBuffersClean\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_pgstatBgWriterMaxWrittenClean(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & maxwritten_clean,
                                     /* the length of the data in bytes */
					sizeof(maxwritten_clean));
            //maxwritten_clean += rnd(1);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterMaxWrittenClean\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_pgstatBgWriterBuffersBackend(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & buffers_backend,
                                     /* the length of the data in bytes */
					sizeof(buffers_backend));
            //buffers_backend += rnd(512);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterBuffersBackend\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_pgstatBgWriterBuffersAllocated(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
    
    switch(reqinfo->mode) {

        case MODE_GET:
            refreshNumbers();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     /* a pointer to the scalar's data */
					(u_char *) & buffers_alloc,
                                     /* the length of the data in bytes */
					sizeof(buffers_alloc));
            //buffers_alloc += rnd(256);
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_pgstatBgWriterBuffersAllocated\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
