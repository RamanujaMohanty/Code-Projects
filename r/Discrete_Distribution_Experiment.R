########################################
####### Binomial distributions  ########
########################################
############## Calcuate pmf CDF ##############################################
### The binomial distribution requires two parameters to define the distribution. 
###The  two parameters are n (the number of Bernoulli trials) and p (the probability of success).

n=10  ### Define n, the number of trials
p=0.5   ### Define p, the probability of success
v=0:n  ### Creates a sequence 0, 1, 2, ..., 10, representing all the possible values of Binom(n,p)


### dbinom function calculates the pmf, i.e., exact probability of any x
### Q1. P(X=3)=? #################
dbinom(3,n,p)
### Q2. P(X=k)=? k=0,1,....,10####
dbinom(v,n,p)
### Q3. P(X=20)=?################
dbinom(20,n,p)

### pbinom function calculates the CDF, i.e., exact cumulative probability at any x
### Q4. P(X<=5)=?###############
pbinom(5,n,p)

### OR
sum(dbinom(0:5,n,p))

### OR
1-sum(dbinom(6:10,n,p))

### Q5. P(X>=4)=?#####################
### P(X>=4)=1-P(X<4)=1-P(X<=3)
1-pbinom(3,n,p)

### OR
sum(dbinom(4:10,n,p))

### Q6. P(X>4)=? ######################
### lower.tail is logical option; 
###if TRUE (default), probabilities are P[X<=x], if FALSE, P[X>x].
pbinom(4,n,p,lower.tail=F)

### OR
sum(dbinom(5:10,n,p))

### OR P(X>4)=1-P(X<=4)
1-pbinom(4,n,p)

### Q7.  P(2<=X<=4)=? ################
pbinom(4,n,p)-pbinom(1,n,p)

### OR
sum(dbinom(2:4,n,p))

############ PLot binomial pmf and CDF ##############
x=0:10
prob=dbinom(x,n,p)
### Plot pmf
plot(x,prob,type="h",xlab="x",ylab="Probability",col="blue", ylim=c(0,0.4),main="Binomial Distribution PMF")

# Plot CDF
cdf = c(0,pbinom(x,n,p))
cdf.plot = stepfun(x,cdf,f=0) 
plot.stepfun(cdf.plot,xlab="x",ylab="F(x)",verticals=FALSE,do.points=TRUE,main="Binomial Distribution CDF",pch=16)

############ Simulate experiments ###########################################################
### To simulate one random Bernoulli trial, we use the binomial distribution 
# and set n=1.
e=10 # simulate 10 independent experiments
n=1 # define 1 observation for this 1 experiment
p=.5 # define the probability of success
rbinom(e,n,p) ### conduct the random simulation

### Simulate binomial distribution
e=10 # simulate 10 independent experiments
n=5 # define 1 observation for each of the 10 independent experiments
rbinom(e,n,p) ### conduct the 10 random simulations

n=100000  ### number of binomial simulations
x=rbinom(n, 10, 0.5)
table(x)  ### table with frequency

t=table(x)/n ### Create a distribution table with probabilities
t
plot(t, ylab="Probability", main="n=10, p=0.5")  ### plot table t
v=0:10    ### Creates a sequence 0, 1, 2, ..., 10
prob=dbinom(v,10,0.5) ### theoretical probabilities
t-prob

########################################
####### other distributions     ########
########################################
##### Hypogeometric distribution########
s=50  # s: number of successes in pupulation
f=100 # f: number of failures in population
n=10  # n: sample size
N=f+s
M=s
low.limit=max(0,n-N+M)
up.limit=min(n,M)
x=low.limit:up.limit
dhyper(x,s,f,n) #pmf
phyper(x,s,f,n) #CDF
rhyper(100,s,f,n) # simulate 100 experiments

##### Negative binomial distribution ########
r=5  # r: target for number of successful trails
p=0.6  # p: probability of success for each trail
x=0:20  # only a proportion of possible values
dnbinom(x,r,p) #pmf
pnbinom(x,r,p) #CDF
rnbinom(30,r,p) # simulate experiments

##### Poisson distribution ################
mu=5  #parameter of Poisson distribution, must be a positive number
x=0:20 # only a proportion of possible values
dpois(x,mu)  #pmf
ppois(x,mu)  #CDF
rpois(30,mu)   #simulate experiments
