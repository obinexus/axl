#ifndef AXL_TAXONOMY_H
#define AXL_TAXONOMY_H

/// Taxonomy categories for verb-noun classification
typedef enum TaxonomyCategory {
    TAXONOMY_NONE = 0,
    
    // Verb categories
    VERB_IDENTITY,    // Identification/declaration (let, const, var)
    VERB_ACTION,      // Actions (=, +, -, etc.)
    VERB_STATE,       // State verbs (is, has, etc.)
    
    // Noun categories
    NOUN_SUBJECT,     // Subject nouns (identifiers on left side)
    NOUN_OBJECT,      // Object nouns (values, literals)
    NOUN_MODIFIER     // Modifiers (adjectives, etc.)
} TaxonomyCategory;

#endif // AXL_TAXONOMY_H