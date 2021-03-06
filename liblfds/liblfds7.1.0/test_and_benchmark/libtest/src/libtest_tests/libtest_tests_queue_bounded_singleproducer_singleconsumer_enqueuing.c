/***** includes *****/
#include "libtest_tests_internal.h"





/****************************************************************************/
#pragma warning( disable : 4100 )

void libtest_tests_queue_bss_enqueuing( struct lfds710_list_asu_state *list_of_logical_processors, struct libshared_memory_state *ms, enum lfds710_misc_validity *dvs )
{
  int
    rv;

  lfds710_pal_uint_t
    loop;

  struct lfds710_queue_bss_element
    element_array[128];

  struct lfds710_queue_bss_state
    qs;

  struct lfds710_misc_validation_info
    vi;

  LFDS710_PAL_ASSERT( list_of_logical_processors != NULL );
  LFDS710_PAL_ASSERT( ms != NULL );
  LFDS710_PAL_ASSERT( dvs != NULL );

  /* TRD : create an empty queue
           enqueue 128 elements
           it's a single producer queue, so we just do this in our current thread
           it's an API test
  */

  *dvs = LFDS710_MISC_VALIDITY_VALID;

  lfds710_queue_bss_init_valid_on_current_logical_core( &qs, element_array, 128, NULL );

  for( loop = 0 ; loop < 127 ; loop++ )
    if( 1 != lfds710_queue_bss_enqueue(&qs, NULL, (void *) loop) )
      *dvs = LFDS710_MISC_VALIDITY_INVALID_TEST_DATA;

  // TRD : at this point enqueuing one more should return 0
  rv = lfds710_queue_bss_enqueue( &qs, NULL, (void *) loop );

  if( rv != 0 )
    *dvs = LFDS710_MISC_VALIDITY_INVALID_TEST_DATA;

  vi.min_elements = vi.max_elements = 127;

  lfds710_queue_bss_query( &qs, LFDS710_QUEUE_BSS_QUERY_VALIDATE, &vi, dvs );

  lfds710_queue_bss_cleanup( &qs, NULL );

  return;
}

#pragma warning( default : 4100 )

