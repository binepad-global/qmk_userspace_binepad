# Usage Hints

## ***1st***, set up the QMK env.

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
2. Fork this repository
3. Clone your fork to your local machine
4. Set up the **userspace** folder
    1. `cd` into this repository's clone directory
    2. Set global **userspace** path:

        ```bash
        qmk config user.overlay_dir="$(realpath .)"
        ```
 
        - the command `realpath` may not be on your system, in which case use `qmk config user.overlay_dir="$(pwd)"`  *// assuming a macOS environment*
        - you <ins>MUST</ins> be located in the cloned **userspace** location for this to work correctly
       - This will be automatically detected if you've `cd`ed into your **userspace** repository, but the above makes your **userspace** available regardless of your shell location.
5. If you want to compile directly from the userspace folder then you can set up the QMK paths
    1. `cd` into the QMK directory
    2. Set the `QMK_HOME` path:

        ```bash
        qmk config user.qmk_home="$(realpath .)"
        ```

6. To see if the values are set correctly, use:

    ```bash
    qmk config -ro
    ```

----------

## BINEPAD's keyboards

### **BNK9**

   ```bash
   make binepad/bnk9:binepad
   ```

;)
