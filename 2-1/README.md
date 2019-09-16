- [მასალები](#org4e88d5a)
  - [[წინა კვირის გამეორება](../1-2/README.md)](#org3cbdd3b)
  - [[ლექციია](../transcripts/Lecture03.pdf)](#org8990fcc)
  - [[ჰენდაუთი](../handouts/07-Arrays-The-Full-Story.pdf)](#orgd3dd568)
  - [ამოცანები](#orgb8ac22e)
- [საკითხები](#orgb8641a6)
  - [Little vs Big Endian](#orgf513ebd)
    - [[What is the advantage of little endian format?](https://softwareengineering.stackexchange.com/questions/95556/what-is-the-advantage-of-little-endian-format/95854)](#org2211f80)
    - [which one do most processors use](#orgf3ef7ba)
    - [[illustration](https://softwareengineering.stackexchange.com/a/223960)](#org5f924df)
    - [extras](#orgd59889c)
  - [floating point](#org4be0d1b)



<a id="org4e88d5a"></a>

# მასალები


<a id="org3cbdd3b"></a>

## [წინა კვირის გამეორება](../1-2/README.md)


<a id="org8990fcc"></a>

## [ლექციია](../transcripts/Lecture03.pdf)


<a id="orgd3dd568"></a>

## [ჰენდაუთი](../handouts/07-Arrays-The-Full-Story.pdf)


<a id="orgb8ac22e"></a>

## ამოცანები

-   [memory/struct](../handouts/memory.pdf)
-   [მსგავსი სავარჯიშო დამოუკიდებლად](../handouts/10-Section-Handout.pdf) და ლისპის კოდი (სავარაუდოდ პირობის ახსნა და დავალებად)


<a id="orgb8641a6"></a>

# საკითხები


<a id="orgf513ebd"></a>

## Little vs Big Endian


<a id="org2211f80"></a>

### [What is the advantage of little endian format?](https://softwareengineering.stackexchange.com/questions/95556/what-is-the-advantage-of-little-endian-format/95854)

In a little endian system, the address of a given value in memory, taken as a 32, 16, or 8 bit width, is the same. taking that &rsquo;16&rsquo; as a 16-bit value (c &rsquo;short&rsquo; on most 32-bit systems) or as an 8-bit value (generally c &rsquo;char&rsquo;) changes only the fetch instruction you use — not the address you fetch from. in short, ‘on little endian systems, casts are a **no-op**.’


<a id="orgf3ef7ba"></a>

### which one do most processors use

little endian


<a id="org5f924df"></a>

### [illustration](https://softwareengineering.stackexchange.com/a/223960)


<a id="orgd59889c"></a>

### extras

<https://www.wikiwand.com/en/Endianness> <https://www.youtube.com/watch?v=NcaiHcBvDR4>


<a id="org4be0d1b"></a>

## floating point
