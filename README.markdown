# Sylvester

**The Music Graph Builder**

Expects a graph of tracks, and a set of tracks to add to the graph.
Adds these tracks to the graph depending on a set of tunable factors.

## Music Analysis

Sylvester attempts to classify music according to a set of parameters, and add new tracks to a graph of tracks in a intelligent manner.

The process is stateless - each request to Sylverster attempts to add tracks to the graph only according to its current settings and the graph handed to it. The same settings and and input will produce the same result.

Possible parameters include:

-   **Similarity**
-   **Tempo**
-   **Mood**
-   **Lyrical Content**

## Interface

Presents a HTML server to which JSON requests are made.


### Graph Building

POST graph, using JSON plaintext payload, to:

    http://<server>:8083/graph

Sylverster adds tracks to a graph. It expects input data to be of form:

    {
        "graph" : {
            "nodes" : [
                {
                    "id" : 1,
                    ...
                },
                ...
            ]
            "edges" : [
                {
                    "head": 1,
                    "tail": 2
                },
                ...
            ]            
        },
        "current" : {
            "id" : 1
        }
        "new" : [
            {
                "id" : 1,
                ...
            },
            ...        
        ]
    }
    
It will return a datastructure of the same format, without the "new" object, or an "error" object:

    {
        "graph" : {
            "nodes" : [
                {
                    "id" : 1,
                    ...
                },
                ...
            ]
            "edges" : [
                {
                    "head": 1,
                    "tail": 2
                },
                ...
            ]            
        }
    }

Error case:

    {
        "error" : {
            "code" : 1,
            "reason" : "i fucked up"  
        }
    }


### Configuration

Sylverster can be tuned to perform differently. 

## Dependencies

This project uses:

-   [Mongoose](http://code.google.com/p/mongoose/)
