# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- team member 1
Charlie Welland
- team member 2
Charlotte Kroll

## Lab Question Answers

Question 1: How did the reliability of UDP change when you added 50% loss to 
your local environment? Why did this occur?

The realiability of the UDP changed when I added the %50 loss to the
local environment. It seemed like half of the packages failed to come through.

Question 2: How did the reliability of TCP change? Why did this occur?

While we told the reliability of TCP to change by %50 for the worse, the packages
still seemed to come through. This is do to the TCP system checking to see if
packages were delivered. If they are not, it will send them again. This is
different than UDP because if a package is not delivered in UDP, it's tough 
luck. Due to this TCP protocol, the packages will still get delivered even 
after calling 
sudo tc qdisc add dev lo parent root netem loss 50%
 
Question 3: How did the speed of the TCP response change? Why might this happen?

The speed of the TCP response slowed significantly. This was due to the TCP
process putting the server in time out while it still made sure all 
previous packages were received. If the packages were not being received on
first attempt, the system would wait till the package was eventually recieved.
This caused the system to slow substantially.
