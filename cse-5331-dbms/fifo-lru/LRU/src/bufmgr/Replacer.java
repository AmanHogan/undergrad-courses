package bufmgr;

import global.GlobalConst;

/**
 * @brief Base class for buffer pool replacement policies.
 */
abstract class Replacer implements GlobalConst {

  /** Reference back to the buffer manager's frame table. */
  protected FrameDesc[] frametab;

  // --------------------------------------------------------------------------

  /**
   * Constructs the replacer, given the buffer manager.
   */
  protected Replacer(BufMgr bufmgr) {
    this.frametab = bufmgr.frametab;
  }

  /**
   * Notifies the replacer of a new page.
   */
  public abstract void newPage(FrameDesc fdesc);

  /**
   * Notifies the replacer of a free page.
   */
  public abstract void freePage(FrameDesc fdesc);

  /**
   * Notifies the replacer of a pined page.
   */
  public abstract void pinPage(FrameDesc fdesc);

  /**
   * Notifies the replacer of an unpinned page.
   */
  public abstract void unpinPage(FrameDesc fdesc);

  /**
   * Selects the best frame to use for pinning a new page.
   * 
   * @return victim frame number, or -1 if none available
   */
  public abstract int pickVictim();

  public abstract void printReplacerInfo();

} // abstract class Replacer implements GlobalConst

