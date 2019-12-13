# Kawa ინტერპრეტატორის გამოყენება

ყველაზე მარტივი გზა 
- სასურველ ედიტორში .scm ფაილის დაედითება
- display ფუნქციით პასუხის პრინტი
- kawa file.scm

## display
hello.scm
```scheme
(define (hello) "hello world")
(display (hello))
(newline)
```

ტერმინალში:
```sh
kawa hello.scm
```

## error handling
ჯავას ერორ მესიჯები საკმაოდ გრძელი შეიძლება იყოს და ტერმინალში წასაკითხად
    მოუხერხებელი. Stackoverflow-ს შემთხვევაში შეიძლება ვერც დაინახოთ, იმიტომ რომ
    scrollback სიგრძეს ცდება. ყველაზე მარტივი მოგვარება ამის

```sh
# no space between 2 and >
kawa hello.scm 2> errors.txt
```
თუ ბრძანება არაფერს დაგიწერთ, ესეეგი შეცდომა მოხდა და errors.txt-ში იქნება მესიჯი
