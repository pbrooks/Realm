======
Realm
======
World tools plugin for Unreal.

Installing
------

- Copy Plugin to your Project/Plugins directory
- Add Realm, RealmExamples to your Plugins section in your uproject.

Module: RealmExamples
-----
Example content and maps to demonstrate usage.


Module: RealmPawn
------

- *TestPawnMovement* Specify a Pawn & Target within a world, ensure that the pawn can move towards the target. Used to ensure team members haven't accidently invalidated the NavMesh in Unreal.

Within the tests, the functional test Actor is stored in a different scene. Such that tests can rig with objects in any game levels and be excluded from production.
