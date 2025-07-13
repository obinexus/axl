// Updated includes in src/cli/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>     // For clock() and CLOCKS_PER_SEC
#include <stdbool.h>  // For boolean type support
#include <axl/core/integration/trie_dag.h>

// Command-line options
typedef struct {
    const char* axml_path;
    const char* axl_path;
    bool preview_mode;
    bool dry_run;
    bool retain_memory;
    bool trace_enabled;
    bool profile_enabled;
    bool use_stdin;     // Read AXL from stdin
    bool use_stdout;    // Write output to stdout
    bool collect_events; // Enable event collection
} CliOptions;

void print_usage(const char* program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -c, --config <path>    Path to AXML configuration file\n");
    printf("  -i, --input <path>     Path to AXL input file\n");
    printf("  --preview              Preview DAG before execution\n");
    printf("  --dry-run              Simulate execution without state changes\n");
    printf("  --retain               Override bust policy to retain memory\n");
    printf("  --trace                Enable DAG traversal debug output\n");
    printf("  --profile              Print memory and execution metrics\n");
    printf("  -h, --help             Display this help message\n");
}

CliOptions parse_cli_args(int argc, char** argv) {
    CliOptions options = {0};
    
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0) {
            if (i + 1 < argc) {
                options.axml_path = argv[++i];
            }
        }
else if (strcmp(argv[i], "--stdin") == 0) {
    options.use_stdin = true;
} 
else if (strcmp(argv[i], "--stdout") == 0) {
    options.use_stdout = true;
}
else if (strcmp(argv[i], "--collect-events") == 0) {
    options.collect_events = true;
}
 else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc) {
                options.axl_path = argv[++i];
            }
        } else if (strcmp(argv[i], "--preview") == 0) {
            options.preview_mode = true;
        } else if (strcmp(argv[i], "--dry-run") == 0) {
            options.dry_run = true;
        } else if (strcmp(argv[i], "--retain") == 0) {
            options.retain_memory = true;
        } else if (strcmp(argv[i], "--trace") == 0) {
            options.trace_enabled = true;
        } else if (strcmp(argv[i], "--profile") == 0) {
            options.profile_enabled = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            exit(0);
        }
    }
    
    return options;
}

int main(int argc, char** argv) {
    // Parse command-line arguments
    CliOptions options = parse_cli_args(argc, argv);
    
    // Validate required arguments
    if (!options.axml_path || !options.axl_path) {
        fprintf(stderr, "Error: Both AXML configuration and AXL input files are required\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Print header
    printf("AXL Compiler v0.1.0 - OBINexus Aegis Project\n");
    printf("Configuration: %s\n", options.axml_path);
    printf("Input: %s\n", options.axl_path);
    
    // Profile start time if enabled
    clock_t start_time = 0;
    if (options.profile_enabled) {
        start_time = clock();
    }
    
    // Execute with busting
    bool result = execute_axl_with_busting(options.axl_path, options.axml_path);
    
    // Profile end time if enabled
    if (options.profile_enabled) {
        clock_t end_time = clock();
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
        printf("Execution time: %.3f ms\n", execution_time);
    }
    
    // Print result
    if (result) {
        printf("Execution completed successfully\n");
    } else {
        fprintf(stderr, "Execution failed\n");
        return 1;
    }
    
    return 0;
}