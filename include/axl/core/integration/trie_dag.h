// include/axl/core/integration/trie_dag.h
#ifndef AXL_TRIE_DAG_INTEGRATION_H
#define AXL_TRIE_DAG_INTEGRATION_H

#include <stdbool.h>

/**
 * Execute an AXL file with AXML configuration
 * @param axl_path Path to AXL source file
 * @param axml_path Path to AXML configuration file
 * @return Success status of execution
 */
bool execute_axl_with_busting(const char* axl_path, const char* axml_path);

#endif // AXL_TRIE_DAG_INTEGRATION_H
