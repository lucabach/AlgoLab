# Surveillance Photograph

Given a city graph where certain intersections have police stations and photo spots, find the maximum number of police officers that can be photographed, where each officer walks through a photo spot on their patrol.

## Approach

- Model as max-flow: each station node is a source (up to its station count), each photo-spot node has capacity equal to its photo count, and each node is split into two halves to enforce the photo capacity constraint.
- Officers can enter photo spots from their neighbors freely, but each photo spot limits how many can pass through it. Run max-flow from a super-source to a super-sink.
