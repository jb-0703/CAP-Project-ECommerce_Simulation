# CAP-Project-ECommerce_Simulation
This C-based simulation demonstrates the trade-offs between Consistency (C) and Availability (A) under a network partition (P) in a distributed e-commerce inventory system.

## Overview
In this simulation, a warehouse holds 1 unit of an item in true stock, which is cached across two regional servers, US-East and US-West. A network partition occurs that prevents the two servers from communicating with the central database. There are two ways the system can handle this network partition:
* Guarantee consistency - CP (Consistency + Partition Tolerance): This mode prioritizes data accuracy by pausing checkout and rejecting orders because the system cannot verify the true stock.
* Guarantee availability - AP (Availability + Partition Tolerance): This mode prioritizes uptime by having both servers continue accepting orders based on their local cache. This will lead to overselling which will trigger a refund workflow.

## Prerequisites
To compile this simulation, you will need:
* A C compiler
* A terminal or command-line environment

## Setup/Compilation
1. Download the 'CAPCode-ECommerce.c' file
2. Compile the source code using the command 'gcc CAPCode-ECommerce.c -o CAPCode-ECommerce'
3. Run the code using the command './CAPCode-ECommerce'
4. Once running, you can follow the simulation by selecting menu options.

## Expected Outputs
1. The simulation starts in CP mode with only 1 unit left in the warehouse/true stock. The US East and West servers reflect the true stock by also only having 1 unit left.
Attempting to place an order as Alice or Bob will result in an error message stating that checkout is paused because the system cannot verify the warehouse stock.
2. Switching to AP mode allows Alice and Bob to successfully place an order. However, when the second order goes through, the true warehouse stock becomes negative which triggers an oversold alert. 

## Limitations
* Because this simulation is simply meant to demonstrate the CAP theorem and the affects of choosing consistency or availability, this program performs a single-threaded sequential execution.
