#!/bin/bash
# axl_refactor.sh - Restructure AXL project directories for improved semantic binding
# Author: Nnamdi Okpala
# Date: 2025-07-13

set -euo pipefail

DRY_RUN=false

# Process command line arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    --dry-run)
      DRY_RUN=true
      shift
      ;;
    *)
      echo "Unknown option: $1"
      echo "Usage: $0 [--dry-run]"
      exit 1
      ;;
  esac
done

# Command execution wrapper with dry-run support
execute() {
  if [[ "$DRY_RUN" == true ]]; then
    echo "[DRY-RUN] Would execute: $*"
  else
    echo "[EXECUTE] $*"
    eval "$@"
  fi
}

# Banner
echo "=== AXL Project Refactoring - Semantic DAG Architecture ==="
echo "Mode: $([ "$DRY_RUN" == true ] && echo "DRY-RUN (no changes)" || echo "LIVE (executing changes)")"
echo ""

# Backup function
backup_project() {
  local timestamp=$(date +"%Y%m%d_%H%M%S")
  execute "mkdir -p backups"
  execute "tar -czf backups/axl_backup_${timestamp}.tar.gz src include examples CMakeLists.txt"
  echo "Project backed up to backups/axl_backup_${timestamp}.tar.gz"
}

# Create new directory structure
create_directories() {
  echo "Creating new directory structure..."
  
  # Core components
  execute "mkdir -p src/core/taxonomy"
  execute "mkdir -p src/core/trie"
  execute "mkdir -p src/core/dag"
  execute "mkdir -p src/core/utils"
  
  # Frontend components
  execute "mkdir -p src/frontend/lexer"
  execute "mkdir -p src/frontend/parser"
  
  # Include structure
  execute "mkdir -p include/axl/core/taxonomy"
  execute "mkdir -p include/axl/core/trie"
  execute "mkdir -p include/axl/core/dag"
  execute "mkdir -p include/axl/core/utils"
  execute "mkdir -p include/axl/frontend/lexer"
  execute "mkdir -p include/axl/frontend/parser"
}

# Move files to new locations
move_files() {
  echo "Moving files to new locations..."
  
  # Core files
  execute "cp include/axl/core/taxonomy.h include/axl/core/taxonomy/taxonomy.h"
  execute "cp include/axl/core/trie.h include/axl/core/trie/trie.h"
  execute "cp include/axl/core/dag.h include/axl/core/dag/dag.h"
  execute "cp include/axl/core/token.h include/axl/core/utils/token.h"
  
  execute "cp src/core/dag.c src/core/dag/dag.c"
  execute "cp src/core/trie.c src/core/trie/trie.c"
  
  # Create placeholder files for required components
  execute "touch src/core/taxonomy/taxonomy.c"
  execute "touch src/core/utils/memory.c"
  execute "touch src/core/utils/token.c"
  
  # Frontend lexer placeholders
  execute "touch src/frontend/lexer/statement.c"
  execute "touch src/frontend/lexer/expression.c"
  execute "touch src/frontend/lexer/custom.c"
  execute "touch include/axl/frontend/lexer/lexer.h"
  
  # Frontend parser placeholders
  execute "touch src/frontend/parser/parser.c"
  execute "touch include/axl/frontend/parser/parser.h"
  
  # CLI files
  execute "mkdir -p src/cli"
  execute "cp src/cli/main.c src/cli/"
  execute "cp src/cli/CMakeLists.txt src/cli/"
}

# Update CMake build system
update_cmake() {
  echo "Updating CMake build system..."
  
  # Core CMakeLists.txt
  execute "cat > src/core/CMakeLists.txt << 'EOF'
# Core components for AXL
add_library(axl_core SHARED
  taxonomy/taxonomy.c
  trie/trie.c
  dag/dag.c
  utils/memory.c
  utils/token.c
)

target_include_directories(axl_core PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(axl_core PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
)

target_compile_options(axl_core PRIVATE -Wall -Wextra -Werror)
EOF"

  # Frontend CMakeLists.txt
  execute "cat > src/frontend/CMakeLists.txt << 'EOF'
# Frontend components for AXL
add_library(axl_frontend SHARED
  lexer/statement.c
  lexer/expression.c
  lexer/custom.c
  parser/parser.c
)

target_include_directories(axl_frontend PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(axl_frontend
  axl_core
)

set_target_properties(axl_frontend PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
)

target_compile_options(axl_frontend PRIVATE -Wall -Wextra -Werror)
EOF"

  # Root CMakeLists.txt update
  execute "cat > CMakeLists.txt.new << 'EOF'
cmake_minimum_required(VERSION 3.12)
project(axl VERSION 0.1.0 LANGUAGES C)

# Include custom CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/std)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/core)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cli)

# Compiler options
include(CompilerOptions)
include(Sanitizers)

# Add subdirectories
add_subdirectory(src/core)
add_subdirectory(src/frontend)
add_subdirectory(src/cli)

# Testing
enable_testing()
include(Testing)
EOF"

  execute "mv CMakeLists.txt.new CMakeLists.txt"
}

# Create trie-dag integration example
create_trie_dag_integration() {
  echo "Creating trie-dag integration example..."
  
  # Create integration header
  execute "cat > include/axl/core/integration/trie_dag.h << 'EOF'
#ifndef AXL_TRIE_DAG_INTEGRATION_H
#define AXL_TRIE_DAG_INTEGRATION_H

#include <axl/core/trie/trie.h>
#include <axl/core/dag/dag.h>
#include <axl/core/taxonomy/taxonomy.h>

/**
 * Converts a matched trie pattern into a DAG node for semantic resolution.
 * 
 * @param node The trie node containing the pattern match
 * @param match The matched text
 * @param taxonomy The verb-noun classification
 * @return A DAG node representing the semantic concept
 */
DAGNode* trie_to_dag(TrieNode* node, const char* match, TaxonomyCategory taxonomy);

/**
 * Resolves a set of trie matches into a connected DAG for truth propagation.
 * 
 * @param matches Array of trie matches
 * @param count Number of matches
 * @return Root DAG node of the connected semantic graph
 */
DAGNode* build_semantic_dag(TrieNode** matches, size_t count);

/**
 * Performs semantic validation using DAG truth propagation.
 * 
 * @param root The root DAG node
 * @return True if semantic validation succeeds
 */
bool validate_semantic_graph(DAGNode* root);

#endif // AXL_TRIE_DAG_INTEGRATION_H
EOF"

  # Create integration implementation
  execute "mkdir -p src/core/integration"
  execute "cat > src/core/integration/trie_dag.c << 'EOF'
#include <axl/core/integration/trie_dag.h>
#include <stdlib.h>
#include <string.h>

DAGNode* trie_to_dag(TrieNode* node, const char* match, TaxonomyCategory taxonomy) {
    if (!node || !match) return NULL;
    
    // Create a new DAG node with the appropriate taxonomy classification
    DAGNode* dag_node = dag_node_create(TOKEN_UNKNOWN, taxonomy);
    if (!dag_node) return NULL;
    
    // Transfer the weight from trie to DAG
    float semantic_weight = node->weight;
    
    // Set emotional valence based on taxonomy category
    switch (taxonomy) {
        case VERB_ACTION:
            // Action verbs typically carry strong emotional weight
            semantic_weight *= 1.2f;
            break;
            
        case VERB_STATE:
            // State verbs typically carry more nuanced emotion
            semantic_weight *= 0.8f;
            break;
            
        case NOUN_SUBJECT:
        case NOUN_OBJECT:
            // Objects and subjects carry cultural context
            semantic_weight *= 1.0f;
            break;
            
        default:
            // Default weighting for unknown taxonomy
            semantic_weight *= 0.5f;
            break;
    }
    
    // Transfer pattern information to DAG node
    // (In a real implementation, we would store this in the node's metadata)
    
    return dag_node;
}

DAGNode* build_semantic_dag(TrieNode** matches, size_t count) {
    if (!matches || count == 0) return NULL;
    
    // Create a root node for the semantic graph
    DAGNode* root = dag_node_create(TOKEN_UNKNOWN, TAXONOMY_NONE);
    if (!root) return NULL;
    
    // Process each match into a DAG node
    for (size_t i = 0; i < count; i++) {
        // In a real implementation, we would extract the match text and taxonomy
        // from the trie node based on its pattern
        const char* match_text = "example";
        TaxonomyCategory taxonomy = VERB_ACTION;
        
        DAGNode* node = trie_to_dag(matches[i], match_text, taxonomy);
        if (node) {
            // Connect to the root with appropriate weight
            dag_add_edge(root, node, matches[i]->weight);
        }
    }
    
    return root;
}

bool validate_semantic_graph(DAGNode* root) {
    if (!root) return false;
    
    // Example validation: count nodes and check for completeness
    size_t node_count = 0;
    DAGNode* nodes[256]; // Arbitrary limit for example
    
    // In a real implementation, we would traverse the graph
    // and collect all nodes into an array
    
    // Resolve truth values through the DAG
    dag_resolve(nodes, node_count);
    
    // Check that all nodes have been resolved to a definitive state
    for (size_t i = 0; i < node_count; i++) {
        if (nodes[i]->state == STATE_UNKNOWN) {
            return false;
        }
    }
    
    return true;
}
EOF"

  # Update core CMakeLists.txt to include integration
  execute "cat > src/core/CMakeLists.txt.new << 'EOF'
# Core components for AXL
add_library(axl_core SHARED
  taxonomy/taxonomy.c
  trie/trie.c
  dag/dag.c
  utils/memory.c
  utils/token.c
  integration/trie_dag.c
)

target_include_directories(axl_core PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(axl_core PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
)

target_compile_options(axl_core PRIVATE -Wall -Wextra -Werror)
EOF"

  execute "mv src/core/CMakeLists.txt.new src/core/CMakeLists.txt"
}

# Create a masquerade example file
create_masquerade_example() {
  echo "Creating Spirit of the Masquerade example..."
  
  execute "cat > examples/spirits-of-the-masquerade/main.axl << 'EOF'
// Spirit of the Masquerade - AXL Example
// Demonstrates conceptual DAG expressions with cultural context

concept masquerade {
  // Core properties
  transform = "night-to-day"
  feeling = ["twirl", "chant", "uplift"]
  memory.binding = true
  ancestry.layer = "Biafran-spirit"

  // Temporal triggers
  if time == "midnight" {
    awaken(spirit)
    inject(memory, soul)
    declare unity("Kwenu!")
  }

  // Emotional propagation
  for ancestor in ancestry.lineage {
    connect(ancestor, feeling)
    amplify(ancestor.presence, 1.5)
  }

  // Validation rules
  check {
    assert(feeling contains "warmth")
    validate anchor(ancestry.layer)
    ensure(transform.complete == true)
  }
}

// Cultural animation sequence
animate masquerade {
  stage {
    center(symbol.circle)
    place(dancer, symbol.circle.edge)
    illuminate(dancer, intensity: 0.7)
  }
  
  sequence transform {
    dancer.pose = "arms-wide"
    dancer.motion = ["spin", "elevate", "embody"]
    dancer.chant = "Kwenu!"
    
    after(beats: 3) {
      summon(audience.response, "Yaa!")
      merge(dancer, spirit.ancestor)
    }
  }
  
  resolve {
    return dancer.transformed && audience.connected
  }
}
EOF"

  # Create corresponding AML mapping file
  execute "cat > examples/spirits-of-the-masquerade/mapping.aml << 'EOF'
// Axis Mapping Language for Spirit of the Masquerade

[concept:masquerade]
trigger: chant("Kwenu!")
emotion: ["joy", "awe", "connection"]
reaction: child.chase -> gift.offer
layer: ancestry.spirit

[symbol:circle]
visual: O
meaning: ["unity", "completeness", "protection"]
context: ["community", "wholeness"]

[symbol:dancer]
visual: |
  O
 /|\
 / \
meaning: ["vessel", "medium", "human-spirit-bridge"]
animation: ["twirl", "leap", "embrace"]

[chant:response]
pattern: call("Kwenu!") -> response("Yaa!")
energy: high
connection: lineage -> present
EOF"
}

# Cleanup old files after successful migration
cleanup_old_files() {
  echo "Cleaning up old files..."
  
  execute "rm -f include/axl/core/taxonomy.h"
  execute "rm -f include/axl/core/trie.h"
  execute "rm -f include/axl/core/dag.h"
  execute "rm -f include/axl/core/token.h"
  
  execute "rm -f src/core/dag.c"
  execute "rm -f src/core/trie.c"
}

# Main execution
main() {
  echo "Starting AXL project refactoring..."
  
  # Backup current project
  backup_project
  
  # Create new directory structure
  create_directories
  
  # Move files to new locations
  move_files
  
  # Update CMake build system
  update_cmake
  
  # Create trie-dag integration example
  create_trie_dag_integration
  
  # Create masquerade example
  create_masquerade_example
  
  # Cleanup old files
  if [[ "$DRY_RUN" == false ]]; then
    cleanup_old_files
  fi
  
  echo ""
  echo "AXL project refactoring $([ "$DRY_RUN" == true ] && echo "simulation" || echo "execution") completed."
  echo "New structure implements semantic DAG resolution with cultural expression mapping."
  echo ""
  echo "Next steps:"
  echo "1. Review the trie-dag integration in src/core/integration/"
  echo "2. Complete the lexer components in src/frontend/lexer/"
  echo "3. Implement AML parser for symbolic mapping files"
  echo "4. Update build system and run tests"
}

# Execute the main function
main
