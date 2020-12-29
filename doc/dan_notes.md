# Dan's programming notes

29/12/2020
----------
Eventually I think we're going to want a `tantrumTestContext_t` to store some global test framework information, but we don't need that _right now_ so I'm not adding it.

Remember this "queue" paradigm that you can see in your head about the invokers.  Could be useful.

I think Mike's idea about setting up suites like this isn't possible:
```C
#define MOODYS_SUITE TANTRUM_NEW_SUITE(SuiteName)

MOODYS_SUITE(TestName0)
{
    //Test code go here
}

MOODYS_SUITE(TestName1){}
MOODYS_SUITE(TestName2){}
MOODYS_SUITE(TestName3){}
```

Fuck!