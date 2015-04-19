

# Our Goal #
On our server, we much keep information for each phone number, and the most trivial method is to use phone number as index in the database system. However, this may result in serious security problems which we do not expecte. In detail, users of our product is unwilling to allow anyone(**hackers,designers,developers,administrators**) having access to his/her phone number and associated personal information. So, it's necessary to propose a method for generating indices from phone numbers, so that it's difficult for anyone to recover the phone numbers from indices.

# Problem Formulation #
The problem can be formulate as below:

  * Given a string n representing the input phone number, output an integer ind as the index generated from strPhoneNumber.

This is just a rough formulation up till now, which **should be updated later**.

# The problem of hashing directly #
The phone number space is so small, which contains at most 20,000,000 numbers in all. An exhaustive search in the phone number space is easy to recover the phone number from the hash value, i.e. preimage attack is of no difficulty.

# About hashing system #
Considering difficulty and realistic issues, choosing an existed hash algorithm may be more secure and more easy to implement. In addition, I think our application doesn't requires extreme security, so using some traditional hash algorithm may be considered. However MD5 proves to be so weak today, so SHA-1 and SHA-2 or their variations might be enough(**discussion?**)

## Implementation Issues ##
We have two choices on how to implement the chosen hash algorithm:
  * Code from scratch by ourselves
  * Using existed library
  * **Our choice? The latter preferred?**


# How to solve the problem of direct hashing (Indexing scheme)? #
This seems to be the most important and also the most difficult part of our design and implementation.

## Proposal from Yuqian Li ##
In addition to the phone number phone, add k different signatures s1,s2,...,sk as inputs. The k signatures are signed by different persons with great reputation. Then the k signatures are padded to the original phone number as the input to the hashing system, which are simply noted as n|s1|s2|...|sk. However because the signatures should be kept in memory to ensure security, the signature should be provided each time the server is restarted, which is not realistic at all.

## Other solutions? ##
  * Not allowing anyone including designers and developers is not an easy task. In fact, Li's proposal also suffers from the pitfall that anyone who has root access to the server still has some way to retrieve the signatures from main memory.
  * I've consulted Mr Zhen Chen, who said that **he hasn't seen any research or application which achieved or tried to achieve our goal**. He thought at least some important administrators must have access to the phone numbers.
  * Mr Chen advised that **key sharing** is still the most commonly used effective way to achieve this kind of security. This is almost same to Li's proposal, except that the signatures are signed and holded by several different administrators in practice.
  * This kind of security is often ensured based on the company's reputation instead of techniques.
  * Any other solutions? This is left as a further research if possible.