# Unix Mutex Examples
Simulation of bidding in Unix System, where processes are bidders.
## Introduction
There is certain number of bidders and items, every bidder bids random item for every bidding round.
* N_AGENTS - number of bidders,
* N_ITEMS - number of items to bid,
* OPENING_BID - starting price of an item,
* NOMINAL_RAISE - raise per bid,
* BIDDING_ROUNDS - number of bidding rounds.
## Example 1
Bidding rounds are implemented by simple loop.
## Example 2
Bidding rounds are implemented by simple loop but prices are stored in shared memory.
## Example 3
Every bidder is a process, they all access shared memory. There are some errors.
## Example 5
Every bidder is a process, they all access shared memory, but memory is protected by single mutex. There are no errors.
## Example 6
Every bidder is a process, they all access shared memory, but every memory cell is protected by uniqe mutex. There are no errors.
