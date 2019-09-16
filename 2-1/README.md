- [მასალები](#orgd7f04bf)
  - [[წინა კვირის გამეორება](../1-2/README.md)](#orgbdadb63)
  - [[ლექციია](../transcripts/Lecture03.pdf)](#orgbcd63b9)
  - [[ჰენდაუთი](../handouts/07-Arrays-The-Full-Story.pdf)](#orgf9154d0)
  - [[ამოცანები](../handouts/10-Section-Handout.pdf)](#orgbccbc6d)
- [საკითხები](#orge5d74d3)
  - [Little vs Big Endian](#org64134e1)
    - [[What is the advantage of little endian format?](https://softwareengineering.stackexchange.com/questions/95556/what-is-the-advantage-of-little-endian-format/95854)](#orgb171bdf)
    - [which one do most processors use](#org22a67bf)
    - [[illustration](https://softwareengineering.stackexchange.com/a/223960)](#org4461f44)
    - [extras](#org98edbb0)



<a id="orgd7f04bf"></a>

# მასალები


<a id="orgbdadb63"></a>

## [წინა კვირის გამეორება](../1-2/README.md)


<a id="orgbcd63b9"></a>

## [ლექციია](../transcripts/Lecture03.pdf)


<a id="orgf9154d0"></a>

## [ჰენდაუთი](../handouts/07-Arrays-The-Full-Story.pdf)


<a id="orgbccbc6d"></a>

## [ამოცანები](../handouts/10-Section-Handout.pdf)


<a id="orge5d74d3"></a>

# საკითხები


<a id="org64134e1"></a>

## Little vs Big Endian


<a id="orgb171bdf"></a>

### [What is the advantage of little endian format?](https://softwareengineering.stackexchange.com/questions/95556/what-is-the-advantage-of-little-endian-format/95854)

In a little endian system, the address of a given value in memory, taken as a 32, 16, or 8 bit width, is the same. taking that &rsquo;16&rsquo; as a 16-bit value (c &rsquo;short&rsquo; on most 32-bit systems) or as an 8-bit value (generally c &rsquo;char&rsquo;) changes only the fetch instruction you use — not the address you fetch from. in short, ‘on little endian systems, casts are a **no-op**.’


<a id="org22a67bf"></a>

### which one do most processors use

little endian


<a id="org4461f44"></a>

### [illustration](https://softwareengineering.stackexchange.com/a/223960)


<a id="org98edbb0"></a>

### extras

<https://www.wikiwand.com/en/Endianness> <https://www.youtube.com/watch?v=NcaiHcBvDR4>
