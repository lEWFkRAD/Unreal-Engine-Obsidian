---
title: "How to start optimizing your Unreal Engine Game"
source: "https://www.youtube.com/watch?v=4lARfWIGU68"
video_id: "4lARfWIGU68"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, optimization, gamedev, blueprint, coding]
---

# How to start optimizing your Unreal Engine Game

**URL:** https://www.youtube.com/watch?v=4lARfWIGU68
**Channel:** UNF Games
**Duration:** 17:54

## Transcript

[00:01] We are almost ready to finish this
[00:03] course. But before doing that, I do want
[00:06] to talk a little about optimization.
[00:10] Optimization is something that you will
[00:12] have to continuously do whenever you're
[00:16] developing a game.
[00:18] Now, what are the tips that I want to
[00:20] share with you? First,
[00:23] every time you make a change, make sure
[00:25] that you're checking here.
[00:28] This little number will tell you how
[00:31] well or how bad your game is running.
[00:34] You may not feel it, especially when you
[00:38] have a lot of frames
[00:41] because if you have 120 frames and you
[00:44] start adding things and you go down to
[00:46] 60, you will still be running your game
[00:49] just fine.
[00:51] But when you go under 60, then you're
[00:53] going to start noticing things. So, I'm
[00:56] going to go to
[00:58] the normal scalability settings, which
[01:01] is epic.
[01:03] And you will notice that immediately I'm
[01:05] using some I'm losing some frames right
[01:08] now.
[01:10] It's bad, but it's not that bad. Why?
[01:13] Because when we release our game, we're
[01:16] going to get rid of a lot of things that
[01:20] are not supposed to be there. For
[01:22] example, right now everything that I
[01:25] have opened thus far is loaded into
[01:28] memory.
[01:30] And that will not be the case with your
[01:32] with our game because it will get things
[01:36] will get loaded
[01:39] as long as we need them. So whenever we
[01:42] need something, boom, it will get loaded
[01:44] into into the game. When we stop using
[01:47] that something, then boom, it will get
[01:49] unloaded. Right? when you're using the
[01:52] editor, Unreal doesn't know which things
[01:54] do you want or not. So, it's going to
[01:56] start loading things just in case. And
[02:00] it's understandable they want you to
[02:02] have a good experience with the editor
[02:06] and having to okay, I want to use this
[02:10] and then I drag and drop it and I need
[02:12] to wait for it to load. Then you can see
[02:15] how that could be a bad user experience.
[02:18] So testing your game inside the editor
[02:20] is not really a real representation
[02:24] of the frames that you can get.
[02:27] But I mean the lowest frames that you
[02:30] can get here should be the lowest frames
[02:32] that you could get during your normal
[02:35] game, your standalone game.
[02:40] That's something to take in
[02:41] consideration. Now
[02:44] what do you need to do whenever you see
[02:46] that your frames are completely
[02:49] bad? The first thing that you need to do
[02:52] is something called profiling. Profiling
[02:56] is just our way of telling the any
[02:59] developer that you need to look exactly
[03:03] what what is causing these these hitches
[03:08] or these low frames. So you need to look
[03:12] for the culprit.
[03:14] To do that, we will use the start unit
[03:18] command. And you can enter console
[03:20] commands here. I think that there is
[03:24] also a way to use the unit start command
[03:28] somewhere hidden in these menus.
[03:32] I'm not sure. But the easier way to do
[03:36] this is just
[03:38] go here, start
[03:42] unit
[03:44] and we can select the first one.
[03:47] Press enter and you will get this new
[03:53] information in your game or in your
[03:55] screen. So, let me just put it like
[03:58] that.
[04:01] Let's talk about what this mean.
[04:03] So,
[04:05] oh, what's this? No, I wanted to write
[04:08] on top of this. Okay, so frame
[04:12] this frame is the milliseconds it takes
[04:15] for your game to render one frame. And
[04:19] if you do the math, you will eventually
[04:21] get the same information here, right?
[04:25] And
[04:27] this is the more updated one because
[04:29] right now this like it's telling me that
[04:34] the last frame was this one. Right
[04:38] now, what are the other information? The
[04:41] other information is all about
[04:44] things in your map like these ones.
[04:51] The memory is being used by your game,
[04:54] the input
[04:56] time that it takes uh that is taking
[04:59] this frame to be processed.
[05:02] And these other ones,
[05:06] especially these three,
[05:08] are threats. What is a thread? Well,
[05:13] your computer
[05:16] has different types of
[05:19] ways to process
[05:21] uh any type of action that it needs to
[05:23] take.
[05:25] So if I want to save a file, you will
[05:28] have the Q to save a file, right? Save.
[05:31] save a file. But what happens if
[05:36] a email gets to my PC and I'm using
[05:39] another program at the same time? Then
[05:42] if we only had one thread, we will need
[05:44] to wait till this finishes and then I
[05:48] can go and do something else in another
[05:51] program.
[05:53] But because
[05:56] it's the future, we have multiple
[05:58] threads. Then if the thread is not doing
[06:02] anything, oh you want to process
[06:04] something, okay, let's process it here.
[06:06] You want to process another thing, let's
[06:08] process it on this thread.
[06:11] In Unreal,
[06:13] we have
[06:15] the game thread.
[06:18] In this thread, we are going to do all
[06:22] the processing that happens inside of
[06:25] our blueprints inside of our C++.
[06:29] So if this is red,
[06:33] it means that you have a programming
[06:36] type of issue. You will need to look
[06:39] around and see
[06:41] what could be happening. Usually some
[06:45] for loops could be the culprit.
[06:48] Maybe you are also
[06:50] spawning a lot of things on the tick,
[06:54] destroying a lot of things on the tick
[06:56] also can can lead to problems. So yeah,
[07:00] there are a lot of issues that you can
[07:03] find. Again, this is also a big topic to
[07:07] to talk about
[07:10] and I will suggest a lot to
[07:13] go to the documentation
[07:15] and there I believe they have published
[07:18] a optimization learning path and this
[07:22] super recommended that you that you
[07:23] check it out so you can take your time
[07:26] checking what could you do about it.
[07:29] Right now that is the game thread. Then
[07:32] is the draw one. The draw thread. It
[07:37] will be related to the things that you
[07:39] have put on your level. How many
[07:43] primitives you have and how many
[07:46] triangles they have,
[07:49] how many materials they are using. So,
[07:53] and I believe even the hat will be
[07:56] processed here.
[07:58] So if this is the problem then it means
[08:02] that yeah you may have too many things
[08:07] clumped together.
[08:10] The GPU time it's it will be anything
[08:14] related usually to visual effects to
[08:16] simulations
[08:18] sometimes also to materials
[08:21] and postprocessing effects. Yeah you you
[08:24] could probably find it there also.
[08:27] This will mean that you have some very
[08:30] heavy visual effects in your level. And
[08:38] the thing about that, okay, you told me
[08:40] we have threads, right? Why am I slowing
[08:44] down? Well, in order for a frame to be
[08:47] processed, all the threats need to
[08:51] finish. So, if this is my game thread,
[08:53] and this one took 0.2 2 milliseconds.
[08:58] This is my draw thread and this one took
[09:02] 0.5.
[09:06] And in my GPU,
[09:08] this one took like one 1.2. Then this
[09:13] one needs to wait and also this one
[09:15] needs to wait until the slowest one
[09:18] finishes. Otherwise, the frame cannot be
[09:20] processed. And when the frame is
[09:22] processed, well, you do this thing
[09:25] again. Why you do it again? Because if
[09:27] you move, then you will get another type
[09:30] of lighting. You will get another type
[09:32] of behaviors in your game.
[09:37] So yeah, that's the thing about this
[09:42] little window, not window, but
[09:46] information that you can put on your
[09:48] window. And take in consideration that
[09:51] depending on where you are in your map,
[09:54] this will change a lot. If I'm looking
[09:57] away,
[09:59] then yeah, I don't have any problem
[10:03] because nothing is being loaded there.
[10:07] You can know this and Unreal does this
[10:09] optimization by itself. If if you just
[10:12] freeze the rendering. So let's freeze
[10:16] rendering.
[10:18] Enter. Rendering is frozen. And if I
[10:20] just look
[10:23] behind me, nothing is being rendered.
[10:28] Yeah, that that that that thing Unreal
[10:30] always does it by itself.
[10:34] And you will see that when I unfreeze
[10:36] it. Just need to type freeze rendering
[10:39] again. Then we actually load stuff. And
[10:42] this will happen even if I do this. It
[10:45] just happened super quick.
[10:48] And depending on where you're looking,
[10:51] your frame could go worse. If I'm
[10:53] looking towards this, then I'm not
[10:56] rendering a lot of things, but I'm
[10:58] rendering this
[11:00] material and or well the foliage and the
[11:03] material foliage. And it also it's
[11:07] different if I'm looking
[11:11] through to my map from a distance.
[11:16] because there is some a thing called
[11:18] LODs the level of detail and that level
[11:21] of detail will change depending on how
[11:24] far am I because here I really don't
[11:27] need that much detail to understand the
[11:30] shape the overall shape so if I again
[11:33] freeze the rendering and go back near
[11:37] this I may find some things that are
[11:41] rendered
[11:43] differently like for example
[11:45] Look at here. There are some leaves that
[11:48] it's not showing me. Or maybe that's how
[11:51] the how the tree is. Let me just
[11:54] unfreeze the rendering.
[11:56] And you will see the actual
[11:58] uh detail of this tree whenever you are
[12:01] close enough. But again, this is done
[12:04] automatically. You don't need to worry.
[12:06] It will happen automatically.
[12:09] And yeah.
[12:13] So things to have in consideration
[12:16] especially if you are suffering in the
[12:18] draw
[12:20] you just need to go here and we have
[12:22] different view modes. We have an unlit
[12:25] view mode you will get more frames here
[12:27] because no illumination but it will
[12:30] looks it would look very bad.
[12:34] We have these optimizations.
[12:36] Uh where is it?
[12:39] Our no buffer optimization view modes.
[12:42] And one of the most important ones will
[12:45] be the shader complexity. Depending on
[12:47] your materials, you will get shaders
[12:51] that are a little bit heavier because
[12:53] they have more instructions in it.
[12:56] What you need to have in consideration
[12:58] is that you don't want to have any any
[13:01] type of material or shader that is
[13:04] white. If it's red, it's fine.
[13:09] It's it's okay. Just don't try just
[13:14] don't try to have everything green
[13:17] because that's not possible unless you
[13:19] want your game to look very bad.
[13:22] So, I mean, it's unavoidable that you
[13:24] have a shader complexity
[13:27] or or certain shader complexity in your
[13:30] level, but try not to, if you will have
[13:34] it, try not to put like too many
[13:37] materials that are causing this in the
[13:41] same place,
[13:43] right? Just try to avoid to reaching the
[13:46] the white part. So, this is actually
[13:50] not bad at all.
[13:55] Let's return to lit.
[13:59] And you probably have heard a lot about
[14:02] nanite.
[14:04] To enable nanite, you can select your
[14:06] mesh and let's just find it here. Right
[14:10] click on it and nanite. You click here
[14:14] and you will enable nanite for this
[14:16] mesh. I won't do it. is going to take
[14:18] some time and you don't really need to
[14:21] use it if your level is small.
[14:24] N only works
[14:27] I mean it work well if you have a mesh
[14:31] that has a lot of triangles
[14:34] like millions of it
[14:37] and you have a big a big map that is
[14:43] using that right? If that does not apply
[14:46] to you, then you will probably lose some
[14:49] frames if you enable nanite for all the
[14:52] meshes here because look at this mesh.
[14:55] Let's open it.
[15:00] Look at the triangles. We're not re
[15:02] reaching even like half a million. So
[15:06] what will be the point of enabling
[15:08] nanite here? There is no point. it it
[15:11] will only add an overhead that will make
[15:15] you lose some frames. Nanite is a great
[15:17] tool. Nanite really makes it uh possible
[15:21] to work with meshes that have a lot of
[15:23] triangles which wasn't possible before.
[15:27] But you need to know when to use it. In
[15:29] our case, it's not going to be really
[15:32] helpful for us. So, I'm not going to
[15:35] enable it. I just show you how would you
[15:38] enable your your your
[15:42] project or your meshes. And whenever you
[15:44] do that, there is also a view mode for
[15:47] that here in nanite visualization. Make
[15:50] sure to check the overdraw.
[15:53] Right now, nothing is using nanite
[15:55] except my landscape.
[15:58] And in the case of my landscape, you
[16:01] just need to avoid like putting too much
[16:05] nanite assets that are very near each
[16:08] other like overlapping themselves
[16:10] because it's going to make you lose a
[16:12] little bit of performance there. But
[16:15] again it's not that restrictive but you
[16:19] do need to take in consideration
[16:21] whenever you are seeing like a bright
[16:24] color like oh let's have
[16:27] let's have a a little bit of
[16:30] of
[16:32] care whenever we are using nanite
[16:36] in our map.
[16:39] But yeah, again this is also another big
[16:43] topic to explore. But I hope that you at
[16:46] least can start profiling your thing. So
[16:50] whenever you ask in the forums, hey my
[16:52] game runs very poorly. You at least know
[16:57] how to
[17:00] how to explain yourself. Like it's not
[17:02] the game, it's not the programming, it's
[17:04] probably all the meshes that I have
[17:06] added to my map. So let me just
[17:10] remove the stat unit and you will see
[17:13] that now my frames are not ideal.
[17:17] This will get solved if I just close
[17:20] this and open my project again. Or I can
[17:24] just go here and change the viewport
[17:27] scalability
[17:29] and I will get gain some some frames.
[17:31] But yeah, I think it's more on the side
[17:35] that I have a lot of things loaded
[17:37] because I added the character and I was
[17:40] testing a lot of things. So yeah, even
[17:41] here the memory it show it showed me the
[17:44] message that oh your your memory is
[17:48] pretty full. So be be very careful.

---

## Related

- ← Previous: [[package_your_Unreal_Engine_5.7_project_and_share_it_with_everyone]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
