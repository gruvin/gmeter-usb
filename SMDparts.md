# Soldering SMD Parts -- It's EASY #
## No, really! ##

For ten long years, I believed soldering tiny SMD parts -- especially those little pins on microprocessors -- was all but impossible to do by hand.  Frankly, I gave up my love of hobby electronics in disgust.

But nothing could be further from the truth!

Go to YouTube and watch the many how-to videos. Look especially for, "drag soldering" used on 0.5mm pitch parts. You won't believe how easy it is to handle 100-pin, 0.5mm pitch ATmega2560's, for example! Believe it or not, you want a bigger, fatter soldering iron tip for this! Intrigued? Read on ...

Honestly, I now far prefer working with SMD than any through-hole, ancient junk. I find it faster, far more convenient and the final results look way prettier.

Here's a clue for you -- it's all about flux -- modern, clear liquid flux! (And desolder braid, when you're starting out. ;-) Modern flux and hand soldering technique changes EVERYTHING and in ways I could not imagine until I saw it and did it for myself. Now, I can effortlessly, confidently handle ANY SMD parts. You can too. Just dare to believe and get studying. `*wink*`

A little vacuum pump hand tool for picking up and placing tiny SMD parts is a great idea, too. These are available from China, on eBay. Search, "SMD vacuum tool". Oh, not the stand-alone pen type (though those are worth the purchase just for the tool tips) but the ones with a separate pump and hoses, are what you want. They're something like a converted aquarium pump, I guess with the one-way valves reversed.

**What about the need for PCBs for SMD work?** OK. So the only small catch is the general need for a printed circuit board. But you can now get full production quality, multi-layer, dirt cheap circuit boards from the likes of [ITead Studio](http://iteadstudio.com) in Shenzhen, China. They call it a, "PCB prototyping service" (actually, OpenPCB or Small Batch Service now, I think) But don't be fooled. It's not the half baked,  and much more expensive stuff you'll find closer to home (presumably). Not by a long shot.

For example, I got ten (minimum quantity) of these gMeter boards for less than USD$45, delivered. (It's even cheaper to get standard green mask boards.) It takes about 15 days from time of order to boards on my doorstep, in Auckland, New Zealand -- give or take Chinese holidays, of course. If like me, you're outside the 52 states, then shipping from China is going to be much cheaper than from the USA, to just about anywhere -- and generally faster, too. Just six days from Shenzhen to Auckland, including customs clearance. Something like 9,000KMs, at a guess.

If you have a laser printer, then there's also the option of making your own boards, using that nifty toner transfer sheets. Look on youTube to learn how to get best results. Personally though, with cost of that stuff and all the fuss of aligned double-sided designs and drilling of holes if there's through-hole parts ... I just don't bother. Instead, I prototype on something like an Arduino or some other pre-existing AVR platform (in this project's case) and just wait for the high quality boards to arrive from China. Having enough other projects going on will make the time fly by anyway.)

Oh -- to order PCBs, you need to provide "Gerber" files -- board edges, top and bottom copper, mask and silk layers. So forget about those proprietary programs, that lock to into a single, hellish expensive board supplier (EasyPCB etc) by not giving you Gerber output. Honestly -- you could easily be talking the difference between $200+ for a couple of half made boards with no mask or silk layers, versus $40 for ten full production quality versions!

I use KiCAD for the PCB design job. It's free and has no limitations of size, hole count, etc.

There's the infamous, "Eagle" for smaller boards. But I got burned when I started maker larger boards, where it then becomes far too costly for the hobbyist -- and you can't export to free programs.

There's also the gEDA suite -- free, open source. Haven't used it.

A new comer and very tempting too is conservatively priced and very powerful AutoTrax DEX 2012, available for at most US$150 -- with no size or hole count limitations! It includes full auto-0routing and 3D view, too! DEX looks great and is theoretically portable, since all its files are something like XML. But I have no experience with it to date -- and I likely won't, because I don't like being forced to use @#$! Windows. Guess I'll miss out.

In any case, all of those options will free you to generate industry standard Gerber files, for use at any factory of your choosing. So the world is your oyster (whatever that means! ;-)

- - - -

Just for fun, [here's an SMD parts video](http://www.youtube.com/watch?v=FO9CHjdqBr8) I enjoyed watching. This guy is really likeable and entertaining. In the video, he seems to be kindly showing you how you can mess about with relative freedom, making all kinds of little mistakes and still get a good final result -- which was totally true in my own bumbling, newbie experience. In reality and with practice however, you will learn more advanced techniques, letting you get things done right first time, without need for any de-soldering braid, most all of the time.

Now I know -- some folks reading these words are gonna feel that I'm just, "full of it", right? I know, because I preached that exact message of disbelief and frustration to anyone who would listen, for TEN YEARS. Trust me. I was WRONG. :P

Just know that most videos you find will show you the same basic, "it kinda works OK enough" techniques (like the one above) which will certainly get you by. But keep searching, because you will come across a few gems that let you really take it to the next level.  For example, I stumbled on a series of video excerpts, from competing commercial soldering course advertisements. Each on their own, these excerpts didn't really tell me much at all -- but they raised questions like, "How did he do that?!" Pieced together however, I got to learn some really cool (and totally non-intuitive) tricks of the trade -- without doing any of the courses, of course! ;-) Those were the ones that got to me where I'm now completely fearless of any SMD parts. It was about a two year process, in my case. YMMV. But it's all good fun!

Gosh -- I could go on and on -- as if I haven't already. Here's some of my own hints ...

**Hint 1**:
Everything is easier, with the right tools. But they don't have to be expensive! _**The one exception is FLUX!**_ Invest in a flux dispensing pen. This is the CLEAR, modern stuff. It's often named, "no clean", though that's not strictly true. You can get the stuff in straight out bottle and use a cotton wool bud if you must (it's cheaper in the long run). But the pens are just so convenient. I cannot stress enough how important using this flux is! The stuff in your solder wire is NOT going to allow you to deal with parts the way this stuff will. This will not be obvious until you learn drag soldering and start to see the way the surface tension of molten solder can work wonder for you, only in the presence of decent flux. (The stuff in the solder wire will do no hard, though -- except make a bit more of a mess.)

**Hint 2**:
Invest in a decent magnifying glass, with built-in light(!) as well as a head-mouted version of the same, also with an LED light attached. A desk/goose-neck mounted magnifier with a ring of white LEDs around its edge is also good ... though I prefer the head-mout job, since it doesn't get in the way so much. I also ended up buying a $30 USB microscope from DealExtreme.com, for real close-up inspection, in those rare cases I just couldn't see a problem with really small parts. The unexpected bonus of this was being able to see dry joints, created by having flux not completely boiled out of solder. You can see the tiny fishers and fractures under the microscope.

**Hint 3**:
I splashed out on one of those hot-air blower, "re-work" soldering stations. Later, I made my own re-flow oven from a cheap "toaster oven", for re-flowing several boards at once, using solder paste and pre-placement. (I don't usually bother with all that fuss though, these days.) Whilst either of those tools work well for safely removing and replacing something like a 100-pin 0.5mm pitch flat pack package, it turns out that an simple bench-top teflon coated electric fry pan also works very well (for single side re-flow, as well.)

**Hint 4**:
My favourite tool and skill I've learned, by far, is using two soldering irons together -- one in each hand. With practice, you can even work without tweezers with this set-up -- though the amount of practice required is like learning to use chop-sticks for eating! :-). This is certainly by far the easiest and fastest way to deal with removing most components -- far better than using hot air. With this technique, I once transferred over 200, 0603 size resistors, capacitors, transistors and regulators from a seriously heat damaged PCB to a replacement board, in less than half the time it took me to place the parts on the the original board in the first place. By the end of that exercise, I had me yet another practiced and honed skill.

**Hint 5**:
Get yourself some eco-friendly PCB Wash (flux remover). I can't stress this enough. There's all kinds of other way to clean up flux, but none as good as full immersion soaking for 30 minutes to an hour in this stuff, then washing off in running water, drying with hot air (hair dryer if that's all you have.) Your boards will come up sparking, as if from a robotic factory. More importably, flux trapped under chips will get cleaned away, so that it doesn't cause odd problems years later, after breaking down and soaking up moisture!

**Hint 6**:
Tweezers are indispensable. But so if a vacuum pick-up tool!

**Hint 7**:
Tipping small parts out of their delivery strips onto the bench, fussing about with tweezers to get the up-side-down ones sorted, struggling to figure out which end of the diodes is the cathode and so on is all great fun. But there's a better way! Take a piece of stiff cardboard (or whatever) and, for each project, use double-sided sticky tape (the thin, clear stuff) to stick down strips of components. Peel back only enough of the plastic keeper strip as needed at a given time and use your vacuum pick-up tool to pick and place the components on your board. You just saved yourself on the order of 60% of both the time and frustration (and "fun") you would otherwise have had.

**Hint 8**:
When you first start out, you will be convinced that you need to buy or build yourself a pick-and place machine of some kind, because your shaky hands and failing eyes are driving you crazy. Trust me though ... by the time you research and buy or build such a machine, your hand-placing skills will be at a stage where you can populate 100 parts on a prototype board in less time than it takes to load up and configure the machine! Don't waste the money ... unless you intend doing your own medium volume production, of course.

**Hint 9**:
Don't bend your back and neck, leaning low over a desk for three hours, placing parts! Obtain or build a small, sturdy box (12" by 6" perhaps) and put it on your desk. Rest your elbows on the desk and work atop the box. Your eyes, your arms and your back will thank you! (I guess you could use one of those fancy, twist and turn every which way PCB holders. I don't happen to have one and I suspect they may not be stable enough, without bolting down, which is not something I want in the middle of my desk, for the elbow rest to work out right.

**Hint 10**:
Wooden clothes pegs (the two-part, spring loaded type) screwed or clamped to you work box, with super-glued extra lengths of wood (I use polished/glazed chop sticks) extending the upper section, can make very useful clamps for both PCBs and individual ICs. (For large flat packs, even 3M BluTack™ is great!) _**Align twice, solder once! :-)**_ Sure, you can tack down one corner pin, then the opposite, then the rest. That works. But far better to have the whole chip aligned perfectly and firmly clamped down, before _any_ solder goes on.

**Hint 11**:
If you get a hot air re-flow iron and want to remove your first flat-pack by heating from the bottom side of a typical FR-4 fibreglass board, for goodness sakes practise first on some old junk computer PCI card or something. If you don't, then you WILL cook your board. If not the first or second ones, then the third, for sure. I guaranty it. Use 340ºC maximum and never hold the air jet stationary in one place for more than a second or two. This method takes PATIENCE and lots of it. Frankly, there are far better methods. But with care, this one will get you by.

**Hint 12**:
Research, learn and practice the drag soldering method. For success, you are going to want 0.3mm solder wire, because even the tiniest blob of solder from 0.5 or 0.7mm wire is going to be too much, in most cases -- then you're back to using de-soldering braid, so you might as well just use the flood and suck method. But that gets expensive, due to the amount of braid you go through -- not to mention the lower strength joints you invariably end up with.

**Hint 13**:
Solder paste. You don't need to get as fancy as it seems you should. Those reflow temperature profiles, like, "4ºC per second cooling" etc. turn out to be about what any typical oven in free air at around sea level will do, just naturally! Granted, those toaster ovens with the brightly glowing orange heaters can exceed the ramp-up rate, due to close proximity. But the older style elements, which just start to glow red -- the becnh-top bake and grill ovens -- can have all four elements (two above, two below) going flat out and only just keep up with the ideal rate specified in most solder paste profiles. You will however need to KNOW what is going on in there. So get a multi-meter with a thermocouple temperature sensor lead, drill a 3mm hole in the back wall of the oven and poke the probe through. Then just watch it carefully. Switch off the heat 1 full 10ºC before the target maximum (205ºC is the practical absolute maximum!) and open the door when that temp. is reached. A little fanning from a bread board will get you close to 4ºC/sec decrease and pulling the tray out once below 150ºC will take care of the rest.

**Hint 14**
Another hard-learned solder paste hint -- don't bother messing about with hot air. All too often, you'll end up either cooking your board, blowing parts off their pads or going mental with impatience. Use tweezers and a soldering iron -- or a reflow oven.

**Hint 15**: So called, "NO CLEAN" solder paste is so named, not because you don't need to clean the residue flux/lacquer, but because you CANNOT clean it away! It is designed to remain on the board, as a protective layer, forever. Frankly, I hate the stuff. It's fine for quick repair work, perhaps. But it's messy, compared to proper, full immersion washed boards, using normal, washable flux. I would never use it for a scratch build. Yucky.

Note however that the NO CLEAN stuff has a long shelf life and is prolific in the catalogues of most every electronics retailer. Don't buy it! The good stuff "needs" to be shipped on ice, over 48 hours maximum -- or so they say. I put "needs" in quotes because in reality, paste dispensing syringes, with their intrinsically well air-sealed containers will easily last six months in your refrigerator, if not for a couple years, as they have in my case. OK, maybe not for stringent and consistent mass production applications. But more than good enough for us home hobbyists. (The much feared problem is potential oxidation, as well as the usual drying up over time for the stuff in lidded pots.) NO CLEAN = BAD, IMHO.

Mine had to come 2,000KM's from Australia and pass through customs by some expensive "urgent" B.S. It arrived well and truly up to room temp, in the middle of summer. I damn near had to sign my soul away before they'd even ship it that distance. But it was fine and still is.

**Hint 16**:
Actually, I hardly ever use paste these days, because I've gotten so fast with the soldering iron and other tools -- though for doing multiple boards in the oven, it's usually faster in the end. The 0.3mm solder wire (which I ended up getting from the opposite side of the globe, since it's so damned rare in these parts!) really made a big difference. Even 0.5mm is too thick. You just get too much solder on everything. It's OK, I  guess. But it generally just makes for an unsightly, blobby mess. Less is definitely more, when it comes to SMD soldering.

**Hint 17**:
Printed circuit boards with HASL (hot air solder levelled) finish will always have too much solder already on the pads of 0.5mm pitch modules. So solder paste, even applied with a decent, stainless steel stencil, is going to fail miserably in most every case -- unless you first take care to braid off every micron of solder you can manage. For prototyping, the best thing for these parts is to just not use paste or oven in the first place. Do everything else in the oven first, then hand solder the 0.5mm parts. The 0.8mm or more parts shouldn't be a problem, though -- mostly because they (should) have solder mask between each pin, which is not usually the case for 0.5mm pitch, not that it would make much difference for them.

If you're lucky enough to have yourself or have access to a pick and place machine and the job warrants it -- or if you just want to use paste for everything because it yields mastery :P -- then just don't use HASL boards! Spend the extra $20 or whatever to go the gold plated route. It's well worth it. (Especially for black mask boards. Yummy eye candy! :P)

**Hint 18**:
Just dive in! You can only get better. And I bet you'll surprise yourself, quicker than you might think. I am _amazed_ how good I now am, at something I believed near impossible for ten long years!
