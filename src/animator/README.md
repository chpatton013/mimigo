Animator
========

##Animation utilities to work with nodes from the Scene Manager.##
Link to the [Scene Manager](https://github.com/chebert/scene-manager#scene-manager)

###A Brief Example###
From the Scene Manager example:
<pre>
|-Scene (Root -- not visible)
   |-Left Shoulder
   |  |-Sphere
   |  |-Upper Arm
   |     |-Cylinder
   |     |-Elbow
   |        |-Forearm
   |           |-Cylinder
   |
   |-Right Shoulder
   |  |-Sphere
   |  |-Upper Arm
   |     |-Cylinder
   |     |-Elbow
   |        |-Forearm
   |           |-Cylinder
   |-"Great" text*

* Not in the scene manager. Just a picture of the word "Great".
</pre>

####The Animation####
Say we want to make the left arm wave, and the text "Great" to appear above both arms.
To accomplish this, we would need several animations. The following is a simple example:

1. The _left shoulder_ rotates by 10 degrees to the right in 0.5s, then 10 degrees to the left in 0.4s, then 10 degrees to the right in 0.4s.
2. the _elbow_ rotates by 90 degrees to the left in 0.4s, then 90 degrees to the right in 0.5s, then 90 degrees to the left in 0.4s.
3. The "Great" text disappears for .2s, then appears for .9s, and disappears.

**Both the _elbow_ and _left shoulder_ should be done rotating at the exact _same_ time.**

###How Animator Can Accomplish This###
An instance of Animator will take control of the _left shoulder_ for the duration of the animation, while another instance takes control of the _elbow_. 

####Operations of Animator####

* move\_to -- translates to the given position _relative to the parent_ given a duration
* move\_by -- translates to the given position _relative to the position of the node at time of application_ (not the time that the Animator is created)
* rotate\_by/scale\_by
* multiply -- in addition to individual move/scale/rotate, **multiple** transformations of any type can be applied at once. This will linearly translate
each element of the transform matrix to the product of the transform matrix*given matrix
* set_to -- sets the transform over a duration
* wait -- do nothing to this node

Each of these operations is given a duration.

* set\_visible -- sets the visiblity at whatever the current frame would be. This does _not_ take a duration.

####Calculation of Duration####
Since durations need to be synced up, times will be calculated in _frames_, given seconds. The number of frames to wait will be calculated by

<code>frames = seconds * frames\_per\_second </code>

A single Animator static update method will be called every frame tick. This animator method will update all instances of Animator in existence.

####Queueing Animations####
Animations can be queued for a given Animator instance, up until the animation has started. Once the animation has started, no more animations can be
queued to it.

####Ownership####
Each Animator object owns itself, and deletes itself when its animation is complete. The Animator does not _own_ any of the nodes that it manages.
