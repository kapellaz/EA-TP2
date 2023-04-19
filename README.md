
# Expanding a Trading Portfolio
## Description:
Your friend John likes to trade in the stock market, in particular, he buys and sells shares from a limited number of companies in his portfolio.

Since things have been going well for him, he decided to add one more company to his portfolio and needs your help. He has collected the daily shares values over the past D days from the N companies that he is thinking of adding to his portfolio. Now, he wants to know which company would have yielded the highest profit over those D days assuming that he traded the shares in the best way possible.

There are a few things to keep in mind:

* As a personal rule, John never wants to have more than K shares from a company.
* On each day John can perform at most one transaction. A transaction is to buy __or__ sell as many shares as he wants from that company.
* The trading exchange that John uses charges a fixed fee R for __every share bought__, for example, if John buy 2 shares in a transaction the exchange fee would be 2 × R. There is no fee when selling shares.

## Tasks
There are three possible tasks.

For the first task (100 points), you have to print the best profit that John could have gotten by trading shares of each company.

For the second task (100 points), for each company, you have to print the best profit and an optimal trading scheme, that is, print the information of how many shares to buy or sell each day to get the best profit.

For the third task (50 points), you have to print the best profit, and how many distinct trading schemes would give that profit value.

## Input
The first line of the input gives an integer 1, 2 or 3, denoting which task to solve.

The second line of the input gives four-space separated integers N, D, K, R.

The following N lines give the daily share values of each company. In particular, the daily share values of a company are given by D space-separated integers V1, V2, …, VD that correspond to the values of one share on day 1, 2, …, D, respectively.

## Output
For task 1, output one line for each company with an integer that corresponds to the best profit that can be obtained trading the shares of that company.

For task 2, output two lines for each company. The first line should contain a single integer that corresponds to the best profit that can be obtained trading the shares of that company. The second line should give a trading scheme for that company that gives the best profit. If there are multiple optimal trading schemes you can print any. The trading scheme should contain D space-separated integers T1, T2, …, TN that denote the transaction operations on days 1, 2, …, N, respectively. A value Ti < 0 means that on day i John should have sold |Ti| shares, a value Ti > 0 means that John should have bough Ti shares, and a value Ti = 0 mean that John should do nothing on that day.

For task 3, output one line for each company with two space-separated integers. The first integer is the best profit that can be achieved for that company, and the second is the number of distinct trading schemes that would result in that profit value. Since this number may be too large print the result modulo 109 + 7. Take into account the following modulo property:

(a+b) mod  m = ((a mod  m)+(b mod  m)) mod  m

## Limits
Time limit: 2 seconds

### Tasks 1 & 2
* 1 ≤ N ≤ 100
* 1 ≤ D ≤ 20000
* 1 ≤ K ≤ 2000
* 1 ≤ R ≤ 100
* 1 ≤ Vi ≤ 5000
### Task 3
* 1 ≤ N ≤ 100
* 1 ≤ D ≤ 50
* 1 ≤ K ≤ 5
* 1 ≤ R ≤ 5
* 1 ≤ Vi ≤ 10
## Example Task 1
### Input
```
1
2 5 3 10
100 20 40 200 170
10 10 40 10 50
```
### Output
```
510
150
```
## Example Task 2
### Input
```
2
2 5 3 10
100 20 40 200 170
10 10 40 10 50
```
### Output
```
510
0 3 0 -3 0
150
1 2 -3 3 -3
```
## Example Task 3
### Input
```
3
2 5 3 10
100 20 40 200 170
10 10 40 10 50
```
### Output
```
510 1
150 4
```